import sys
import os
import re
import time
import ctypes
import signal
# ──────────────────────────────────────────────────────────────────────────────
# Win32 constants
# ──────────────────────────────────────────────────────────────────────────────
ENABLE_VIRTUAL_TERMINAL_PROCESSING = 0x0004
ENABLE_PROCESSED_OUTPUT            = 0x0001
STD_OUTPUT_HANDLE  = -11
PROCESS_TERMINATE  = 0x0001
WS_THICKFRAME      = 0x00040000
WS_MAXIMIZEBOX     = 0x00010000
GWL_STYLE          = -16
SWP_NOMOVE         = 0x0002
SWP_NOSIZE         = 0x0001
SWP_NOZORDER       = 0x0004
SWP_FRAMECHANGED   = 0x0020
KEYEVENTF_KEYUP    = 0x0002
VK_LWIN            = 0x5B
VK_LEFT            = 0x25
CTRL_C_EVENT       = 0
CTRL_CLOSE_EVENT   = 2
DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2 = ctypes.c_void_p(-4)
DOS_CELL_W = 9
DOS_CELL_H = 16
kernel32 = ctypes.windll.kernel32
user32   = ctypes.windll.user32
shcore   = ctypes.windll.shcore
# ──────────────────────────────────────────────────────────────────────────────
# Win32 structures
# ──────────────────────────────────────────────────────────────────────────────
class COORD(ctypes.Structure):
    _fields_ = [("X", ctypes.c_short), ("Y", ctypes.c_short)]
class SMALL_RECT(ctypes.Structure):
    _fields_ = [("Left",  ctypes.c_short), ("Top",    ctypes.c_short),
                ("Right", ctypes.c_short), ("Bottom", ctypes.c_short)]
class CONSOLE_SCREEN_BUFFER_INFO(ctypes.Structure):
    _fields_ = [("dwSize",              COORD),
                ("dwCursorPosition",    COORD),
                ("wAttributes",         ctypes.c_ushort),
                ("srWindow",            SMALL_RECT),
                ("dwMaximumWindowSize", COORD)]
class CONSOLE_FONT_INFOEX(ctypes.Structure):
    _fields_ = [("cbSize",     ctypes.c_ulong),
                ("nFont",      ctypes.c_ulong),
                ("dwFontSize", COORD),
                ("FontFamily", ctypes.c_uint),
                ("FontWeight", ctypes.c_uint),
                ("FaceName",   ctypes.c_wchar * 32)]
class CONSOLE_CURSOR_INFO(ctypes.Structure):
    _fields_ = [("dwSize", ctypes.c_ulong), ("bVisible", ctypes.c_bool)]
class RECT(ctypes.Structure):
    _fields_ = [("left",  ctypes.c_long), ("top",    ctypes.c_long),
                ("right", ctypes.c_long), ("bottom", ctypes.c_long)]
# ──────────────────────────────────────────────────────────────────────────────
# Win32 helpers
# ──────────────────────────────────────────────────────────────────────────────
def enable_vt_mode():
    h = kernel32.GetStdHandle(STD_OUTPUT_HANDLE)
    mode = ctypes.c_ulong(0)
    kernel32.GetConsoleMode(h, ctypes.byref(mode))
    kernel32.SetConsoleMode(h, mode.value
                            | ENABLE_VIRTUAL_TERMINAL_PROCESSING
                            | ENABLE_PROCESSED_OUTPUT)
def hide_cursor():
    h = kernel32.GetStdHandle(STD_OUTPUT_HANDLE)
    ci = CONSOLE_CURSOR_INFO(dwSize=1, bVisible=False)
    kernel32.SetConsoleCursorInfo(h, ctypes.byref(ci))
def clear_screen():
    sys.stdout.write("\x1b[2J\x1b[3J\x1b[H")
    sys.stdout.flush()
def get_console_size():
    h = kernel32.GetStdHandle(STD_OUTPUT_HANDLE)
    csbi = CONSOLE_SCREEN_BUFFER_INFO()
    if kernel32.GetConsoleScreenBufferInfo(h, ctypes.byref(csbi)):
        cols = csbi.srWindow.Right  - csbi.srWindow.Left + 1
        rows = csbi.srWindow.Bottom - csbi.srWindow.Top  + 1
        return max(1, cols), max(1, rows)
    return 80, 25
def get_cell_size():
    h = kernel32.GetStdHandle(STD_OUTPUT_HANDLE)
    cfi = CONSOLE_FONT_INFOEX()
    cfi.cbSize = ctypes.sizeof(CONSOLE_FONT_INFOEX)
    if kernel32.GetCurrentConsoleFontEx(h, False, ctypes.byref(cfi)):
        w, ht = cfi.dwFontSize.X, cfi.dwFontSize.Y
        if w > 0 and ht > 0:
            return w, ht
    return 8, 16
def apply_console_size(cols, rows):
    h = kernel32.GetStdHandle(STD_OUTPUT_HANDLE)
    kernel32.SetConsoleScreenBufferSize(h, COORD(X=max(cols+10,120), Y=max(rows+10,50)))
    kernel32.SetConsoleWindowInfo(h, True,
        ctypes.byref(SMALL_RECT(Left=0, Top=0, Right=cols-1, Bottom=rows-1)))
    kernel32.SetConsoleScreenBufferSize(h, COORD(X=cols, Y=rows))
    time.sleep(0.06)
def lock_window_size():
    hwnd = kernel32.GetConsoleWindow()
    if not hwnd:
        return
    style = user32.GetWindowLongPtrW(hwnd, GWL_STYLE)
    style &= ~(WS_THICKFRAME | WS_MAXIMIZEBOX)
    user32.SetWindowLongPtrW(hwnd, GWL_STYLE, style)
    user32.SetWindowPos(hwnd, None, 0, 0, 0, 0,
        SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED)
def snap_left():
    hwnd = kernel32.GetConsoleWindow()
    if not hwnd:
        return
    user32.ShowWindow(hwnd, 5)
    time.sleep(0.16)
    user32.BringWindowToTop(hwnd)
    user32.SetForegroundWindow(hwnd)
    user32.keybd_event(VK_LWIN, 0, 0, 0)
    time.sleep(0.04)
    user32.keybd_event(VK_LEFT, 0, 0, 0)
    time.sleep(0.04)
    user32.keybd_event(VK_LEFT, 0, KEYEVENTF_KEYUP, 0)
    time.sleep(0.04)
    user32.keybd_event(VK_LWIN, 0, KEYEVENTF_KEYUP, 0)
    time.sleep(0.5)
    hwnd_m = user32.FindWindowA(None, b"DailyRoutine.exe")
    if hwnd_m and user32.IsWindow(hwnd_m):
        user32.SetForegroundWindow(hwnd_m)
def kill_parent():
    hwnd = user32.FindWindowA(None, b"DailyRoutine.exe")
    if hwnd and user32.IsWindow(hwnd):
        pid = ctypes.c_ulong(0)
        user32.GetWindowThreadProcessId(hwnd, ctypes.byref(pid))
        if pid.value:
            hp = kernel32.OpenProcess(PROCESS_TERMINATE, False, pid.value)
            if hp:
                kernel32.TerminateProcess(hp, 0)
                kernel32.CloseHandle(hp)
# ──────────────────────────────────────────────────────────────────────────────
# Signal / Ctrl-C handlers
# ──────────────────────────────────────────────────────────────────────────────
_HandlerRoutine = ctypes.WINFUNCTYPE(ctypes.c_bool, ctypes.c_ulong)
def _setup_handlers():
    def _ctrl(event):
        if event in (CTRL_C_EVENT, CTRL_CLOSE_EVENT):
            kill_parent()
            return True
        return False
    ref = _HandlerRoutine(_ctrl)
    kernel32.SetConsoleCtrlHandler(ref, True)
    def _sig(s, f):
        kill_parent(); sys.exit(0)
    signal.signal(signal.SIGINT,  _sig)
    signal.signal(signal.SIGTERM, _sig)
    return ref
# ──────────────────────────────────────────────────────────────────────────────
# Color palettes
# ──────────────────────────────────────────────────────────────────────────────
PALETTE_16 = [
    (  0,   0,   0), (170,   0,   0), (  0, 170,   0), (170, 170,   0),
    (  0,   0, 170), (170,   0, 170), (  0, 170, 170), (170, 170, 170),
    ( 85,  85,  85), (255,  85,  85), ( 85, 255,  85), (255, 255,  85),
    ( 85,  85, 255), (255,  85, 255), ( 85, 255, 255), (255, 255, 255),
]
def _build_256():
    p = list(PALETTE_16)
    for r in range(6):
        for g in range(6):
            for b in range(6):
                p.append((0 if r==0 else 55+r*40,
                          0 if g==0 else 55+g*40,
                          0 if b==0 else 55+b*40))
    for i in range(24):
        v = 8 + i*10; p.append((v,v,v))
    return p
PALETTE_256 = _build_256()
# ──────────────────────────────────────────────────────────────────────────────
# ESC fix
# ──────────────────────────────────────────────────────────────────────────────
_BARE_CSI = re.compile(r'(?<!\x1b)\[([0-9;:<=>?]*[A-Za-z])')
def _fix_escapes(text):
    return _BARE_CSI.sub('\x1b[\\1', text)
# ──────────────────────────────────────────────────────────────────────────────
# ANSI -> 2-D grid parser
# ──────────────────────────────────────────────────────────────────────────────
def _blank():
    return {'ch': ' ', 'fg': None, 'bg': None}
def parse_ansi_to_grid(content):
    content = _fix_escapes(content)
    rows = [[]]
    row  = 0
    col  = 0
    fg   = None
    bg   = None
    def ensure(r, c):
        while len(rows) <= r:
            rows.append([])
        while len(rows[r]) <= c:
            rows[r].append(_blank())
    def put(ch):
        nonlocal col
        ensure(row, col)
        rows[row][col] = {'ch': ch, 'fg': fg, 'bg': bg}
        col += 1
    i = 0
    n = len(content)
    while i < n:
        c = content[i]
        if c == '\x1b' and i+1 < n and content[i+1] == '[':
            i += 2
            seq   = []
            cur   = ''
            final = None
            while i < n:
                ch = content[i]; i += 1
                if ch.isalpha():
                    seq.append(int(cur) if cur.isdigit() else 0)
                    final = ch
                    break
                elif ch == ';':
                    seq.append(int(cur) if cur.isdigit() else 0)
                    cur = ''
                else:
                    cur += ch
            if final is None:
                continue
            if final in ('H','f'):
                row = max(0, (seq[0] if len(seq)>0 else 1) - 1)
                col = max(0, (seq[1] if len(seq)>1 else 1) - 1)
            elif final == 'A': row  = max(0, row - (seq[0] if seq else 1))
            elif final == 'B': row += seq[0] if seq else 1
            elif final == 'C': col += seq[0] if seq else 1
            elif final == 'D': col  = max(0, col - (seq[0] if seq else 1))
            elif final == 'G': col  = max(0, (seq[0] if seq else 1) - 1)
            elif final == 'd': row  = max(0, (seq[0] if seq else 1) - 1)
            elif final == 'm':
                params = seq if seq else [0]
                pi = 0
                while pi < len(params):
                    p = params[pi]
                    if   p == 0:          fg = bg = None
                    elif 30 <= p <= 37:   fg = PALETTE_16[p-30]
                    elif p == 38:
                        if pi+2 < len(params) and params[pi+1] == 5:
                            fg = PALETTE_256[params[pi+2] % 256]; pi += 2
                        elif pi+4 < len(params) and params[pi+1] == 2:
                            fg = (params[pi+2], params[pi+3], params[pi+4]); pi += 4
                    elif p == 39:         fg = None
                    elif 40 <= p <= 47:   bg = PALETTE_16[p-40]
                    elif p == 48:
                        if pi+2 < len(params) and params[pi+1] == 5:
                            bg = PALETTE_256[params[pi+2] % 256]; pi += 2
                        elif pi+4 < len(params) and params[pi+1] == 2:
                            bg = (params[pi+2], params[pi+3], params[pi+4]); pi += 4
                    elif p == 49:         bg = None
                    elif 90 <= p <= 97:   fg = PALETTE_16[p-90+8]
                    elif 100 <= p <= 107: bg = PALETTE_16[p-100+8]
                    pi += 1
            continue
        if c == '\r':
            col = 0
            if i+1 < n and content[i+1] == '\n':
                i += 1
            row += 1
            while len(rows) <= row:
                rows.append([])
        elif c == '\n':
            row += 1
            col = 0
            while len(rows) <= row:
                rows.append([])
        elif c == '\t':
            col = (col//8+1)*8
        elif ord(c) >= 32:
            put(c)
        i += 1
    if not rows or rows == [[]]:
        return [[_blank()]]
    width = max((len(r) for r in rows), default=1)
    for r in rows:
        while len(r) < width:
            r.append(_blank())
    return rows
# ──────────────────────────────────────────────────────────────────────────────
# Integer-only downscale
# ──────────────────────────────────────────────────────────────────────────────
def scale_grid(grid, target_cols, target_rows):
    src_rows = len(grid)
    src_cols = len(grid[0]) if grid else 1
    if target_cols >= src_cols and target_rows >= src_rows:
        return grid
    step_c = max(1, src_cols // target_cols)
    step_r = max(1, src_rows // target_rows)
    out = []
    r = 0
    while r < src_rows and len(out) < target_rows:
        row_out = []
        c = 0
        while c < src_cols and len(row_out) < target_cols:
            row_out.append(grid[r][c])
            c += step_c
        out.append(row_out)
        r += step_r
    return out
# ──────────────────────────────────────────────────────────────────────────────
# Compute target size
# ──────────────────────────────────────────────────────────────────────────────
def compute_target(img_cols, img_rows, term_cols, term_rows, cell_w, cell_h):
    src_px_w   = img_cols * DOS_CELL_W
    src_px_h   = img_rows * DOS_CELL_H
    avail_px_w = term_cols * cell_w
    avail_px_h = term_rows * cell_h
    scale      = min(avail_px_w / src_px_w, avail_px_h / src_px_h)
    tgt_cols   = max(1, int(src_px_w * scale / cell_w))
    tgt_rows   = max(1, int(src_px_h * scale / cell_h))
    return tgt_cols, tgt_rows
# ──────────────────────────────────────────────────────────────────────────────
# Letterbox / pillarbox
# ──────────────────────────────────────────────────────────────────────────────
def add_letterbox(grid, total_cols, total_rows):
    img_rows = len(grid)
    img_cols = len(grid[0]) if grid else 0
    pad_top  = (total_rows - img_rows) // 2
    pad_left = (total_cols - img_cols) // 2
    empty = [_blank() for _ in range(total_cols)]
    out   = []
    for _ in range(pad_top):
        out.append(list(empty))
    for src_row in grid:
        left  = [_blank() for _ in range(pad_left)]
        right = [_blank() for _ in range(total_cols - img_cols - pad_left)]
        out.append(left + list(src_row) + right)
    while len(out) < total_rows:
        out.append(list(empty))
    return out
# ──────────────────────────────────────────────────────────────────────────────
# Grid -> ANSI renderer
# ──────────────────────────────────────────────────────────────────────────────
def render_grid(grid):
    out    = []
    cur_fg = cur_bg = 'UNSET'
    for ri, row in enumerate(grid):
        if ri > 0:
            out.append('\n')
        for cell in row:
            fg = cell['fg']
            bg = cell['bg']
            ch = cell['ch']
            if fg != cur_fg:
                out.append("\x1b[39m" if fg is None
                           else f"\x1b[38;2;{fg[0]};{fg[1]};{fg[2]}m")
                cur_fg = fg
            if bg != cur_bg:
                out.append("\x1b[49m" if bg is None
                           else f"\x1b[48;2;{bg[0]};{bg[1]};{bg[2]}m")
                cur_bg = bg
            out.append(ch)
    out.append("\x1b[0m")
    return ''.join(out)
# ──────────────────────────────────────────────────────────────────────────────
# Display
# ──────────────────────────────────────────────────────────────────────────────
def display(grid):
    img_rows = len(grid)
    img_cols = len(grid[0]) if grid else 1
    term_cols, term_rows = get_console_size()
    cell_w, cell_h       = get_cell_size()
    tgt_cols, tgt_rows = compute_target(
        img_cols, img_rows, term_cols, term_rows, cell_w, cell_h)
    scaled = scale_grid(grid, tgt_cols, tgt_rows)
    framed = add_letterbox(scaled, term_cols, term_rows)
    output = render_grid(framed)
    clear_screen()
    sys.stdout.write(output)
    sys.stdout.flush()
    hide_cursor()
    return term_cols, term_rows

# ──────────────────────────────────────────────────────────────────────────────
# METODO SFONDO (0-15)
# ──────────────────────────────────────────────────────────────────────────────
current_bg_color = 0

def set_background_color(color_index: int):
    global current_bg_color
    if not (0 <= color_index <= 15):
        color_index = 0
    current_bg_color = color_index

    if color_index <= 7:
        bg_code = 40 + color_index
    else:
        bg_code = 100 + (color_index - 8)

    clear_screen()
    sys.stdout.write(f"\x1b[0m\x1b[{bg_code}m")

    term_cols, term_rows = get_console_size()
    for _ in range(term_rows):
        sys.stdout.write(" " * term_cols + "\x1b[K\n")

    sys.stdout.flush()
    hide_cursor()


# ──────────────────────────────────────────────────────────────────────────────
# Main loop
# ──────────────────────────────────────────────────────────────────────────────
CMD_PATH   = "ascii_command.txt"
BGS_FOLDER = "bgs"

def resolve_path(cmd):
    filename = cmd.split(';')[0].strip()
    base = os.path.join(BGS_FOLDER, filename)
    if os.path.isfile(base):
        return base
    if '.' not in filename:
        p = base + ".ansi"
        if os.path.isfile(p):
            return p
    return None

def run():
    try:
        shcore.SetProcessDpiAwarenessContext(
            DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2)
    except Exception:
        pass
    enable_vt_mode()
    kernel32.SetConsoleOutputCP(65001)
    kernel32.SetConsoleCP(65001)
    kernel32.SetConsoleTitleA(b"Eyes")
    time.sleep(0.2)
    _ctrl_ref = _setup_handlers()
    sys.stdout.write("\n*")
    sys.stdout.flush()
    snap_left()
    lock_window_size()
    last_cmd       = ""
    current_grid   = None
    last_term_size = (0, 0)

    while True:
        hwnd_m = user32.FindWindowA(None, b"DailyRoutine.exe")
        if not hwnd_m or not user32.IsWindow(hwnd_m):
            sys.exit(0)

        if os.path.isfile(CMD_PATH):
            try:
                with open(CMD_PATH, "r", encoding="utf-8", errors="replace") as f:
                    cmd = f.readline().strip()
            except OSError:
                cmd = ""

            if cmd and cmd != last_cmd:
                # === GESTIONE SFONDO ===
                if cmd.startswith("bg:"):
                    try:
                        color_idx = int(cmd.split(":", 1)[1].strip())
                        set_background_color(color_idx)
                        current_grid = None
                    except:
                        pass
                else:
                    # === LOGICA ORIGINALE ANSI ART ===
                    path = resolve_path(cmd)
                    if not path:
                        clear_screen()
                        sys.stdout.write(
                            f"\x1b[31;1mERROR: bgs/{cmd.split(';')[0]} not found\x1b[0m\n")
                        sys.stdout.flush()
                        current_grid = None
                    else:
                        with open(path, "rb") as f:
                            content = f.read().decode("utf-8", errors="replace")
                        current_grid   = parse_ansi_to_grid(content)
                        last_term_size = display(current_grid)

                last_cmd = cmd
                try:
                    open(CMD_PATH, "w").close()
                except OSError:
                    pass

        elif current_grid is not None:
            cur_size = get_console_size()
            if cur_size != last_term_size:
                last_term_size = display(current_grid)

        time.sleep(0.1)

if __name__ == "__main__":
    run()