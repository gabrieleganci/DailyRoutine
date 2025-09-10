#include<iostream>
#include<cmath>
#include <conio.h>
#include<Windows.h>
#include <clocale>
#include<string>
#include <chrono>
#include<fstream>
#include <thread>
#include <filesystem>
#include<mmsystem.h>
#include<fstream>
#include<stdexcept>
#include<limits>
#include <cstdlib>
#include<mciapi.h>
#include<tchar.h>
#include<functional>
#include<atomic>
#include<mutex>
#include<map>
#include<sstream>
#include<vector>
#include<unistd.h>
#include<cstdio>
#include<atomic>
#pragma comment(lib, "winmm.lib")
using namespace std;
using namespace std::chrono;
namespace fs = std::filesystem;


void delete_slow(std::ostream& out, int num_chars_to_delete, int millis) {
    for (int i = 0; i < num_chars_to_delete; ++i) {
        if (kbhit()) {
            break; // Se l'utente preme un tasto, interrompi la cancellazione
        }
        out << '\b' << ' ' << '\b'; // Backspace, spazio per cancellare, poi torna indietro
        out.flush();
        Sleep((DWORD)millis);
    }
}

void stampaRigaPerRiga(const std::vector<std::string>& righe, int msPerRiga, int msPerChar) {
    for (const std::string& riga : righe) {
        for (char c : riga) {
            std::cout << c << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(msPerChar));
        }
        std::cout << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(msPerRiga));
    }
}

void KeepWindowOnTop(HWND hwnd) {
    SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
}

void SetFontSize(int fontSizeY) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) {
        std::cerr << "Deam, error" << std::endl;
        return;
    }

    CONSOLE_FONT_INFOEX fontInfo = { 0 };
    fontInfo.cbSize = sizeof(CONSOLE_FONT_INFOEX); 
    fontInfo.nFont = 0;                           
    fontInfo.dwFontSize.X = 0;                    
    fontInfo.dwFontSize.Y = fontSizeY;            
    fontInfo.FontFamily = FF_DONTCARE;            
    fontInfo.FontWeight = FW_NORMAL;              
    wcscpy_s(fontInfo.FaceName, L"Consolas");

    
    if (!SetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo)) {
        ;
    } else {
        ;
    }
}

void cambiaColoreSfondo(int coloreSfondo, int coloreTesto) {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    int attributoColore = (coloreSfondo << 4) | coloreTesto;
    SetConsoleTextAttribute(console, attributoColore);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(console, &csbi);
    DWORD scritto;
    DWORD dimensioneConsole = csbi.dwSize.X * csbi.dwSize.Y;
    COORD homeCoords = {0, 0};
    FillConsoleOutputAttribute(console, attributoColore, dimensioneConsole, homeCoords, &scritto);
    FillConsoleOutputCharacter(console, ' ', dimensioneConsole, homeCoords, &scritto);
}

void displayProgressBar(int progress, int total) {
    const int barWidth = 50;
    float fraction = (float)progress / total;
    int pos = barWidth * fraction;

    std::cout << "[";
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) std::cout << "=";
        else if (i == pos) std::cout << "";
        else std::cout << " ";
    }
    std::cout << "] " << int(fraction * 100.0) << " %\r";
    std::cout.flush();
}

void print_slow(std::ostream& out, const std::string& s, int millis) {
    std::string::size_type sz = s.length();
    for (std::string::size_type i = 0; i < sz; i++) {
        if (kbhit()) {
            out << s.substr(i);
            break;
        }
        out << s[i];
        Sleep((DWORD)millis);
	}
}

int main() {

    SetConsoleTitle("DailyRoutine.exe");

    CONSOLE_FONT_INFOEX fontInfo = { 0 };
        fontInfo.cbSize = sizeof(CONSOLE_FONT_INFOEX); 
        fontInfo.nFont = 0;                           
        fontInfo.dwFontSize.X = 0;                    
        fontInfo.dwFontSize.Y = 24;                   
        fontInfo.FontFamily = FF_DONTCARE;            
        fontInfo.FontWeight = FW_NORMAL;              
        wcscpy_s(fontInfo.FaceName, L"Consolas");     

    const int maxSteps = 3;
    const int animationDuration = 2000; 
    const int frameDelay = 300;
    int elapsed = 0;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    (!SetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo));   

    const int total = 100;

   setlocale(LC_ALL, "Italian");
   HANDLE hc = GetStdHandle(STD_OUTPUT_HANDLE);

    cambiaColoreSfondo(0,15);

    int a,b,c,d,e,f,g,h,j,k,l,m,n,o,p,q,r,s,t,u,v,w,z,aa,ab,ac,ad,ae,af,ag,ah,ai,aj,ak,al,am,an,ao,ap,aq,ar,as,at,au,av,aw,ax,ay,az,ba,bb,bc,bd,be,bf,bg,bh,
    na,nb,zzz,xxx,nc,nd,ne,nf,ng,nh,ni,nj,nk,nm,nn,no,np,nq,ns,nt,nu,nv,nw,nx,ny,nz,eh,qq,jj,gg;
    string nome;
    HWND hwnd = GetConsoleWindow(); 
    KeepWindowOnTop(hwnd);
    Sleep(150);
    PlaySound(TEXT("./music/intro.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    print_slow(cout,"\nInsert Your Name: ",50);
    cin>>nome;
    print_slow(cout,"\nChose the language / Scegli la lingua\n\n1)ENG            2)ITA\n\n",50);
    cin>>zzz;
    system("cls");
    Sleep(200);
    print_slow(cout,"\nRemember to stay connected while playing ( ",30); 
    for (int step = 1; step <= maxSteps; ++step) {
        std::cout << std::string(step, '.') << std::flush;  
        std::this_thread::sleep_for(std::chrono::milliseconds(frameDelay));  
    }
    print_slow(cout," )",60);
    Sleep(100);
    SetConsoleTextAttribute(hc, 0x0C);
    print_slow(cout,"\n\n[Interact With The Program Only When Asked To]\n[You Can Pause By selecting Any Part of The Terminal]\n[You Can Unpause By Right Clicking]\n",60);
    Sleep(500);
    SetConsoleTextAttribute(hc, 0x02);
    print_slow(cout,"\nAnd remember, eyes on me.",30);
    SetConsoleTextAttribute(hc, 0x0F);
    Sleep(1500);
    system("cls");
    for (int i = 0; i <= total; ++i) {
        displayProgressBar(i, total);
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }

    switch (zzz)
    {

    case 0:{
        system("cls");
        cambiaColoreSfondo(0,15);
        for (int i = 0; i <= total; ++i) {
        displayProgressBar(i, total);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));}
        goto label2;
    }
    case 1:{
    label2: 
    PlaySound(NULL, NULL, 0);
    PlaySound(TEXT("./music/piedi.wav"), NULL, SND_FILENAME | SND_ASYNC);
    system("cls");
    cambiaColoreSfondo(7,0);
    std::vector<std::string> testo = {R"(
 ______      _ _         ______            _   _            
 |  _  \    (_) |        | ___ \          | | (_)           
 | | | |__ _ _| |_   _   | |_/ /___  _   _| |_ _ _ __   ___ 
 | | | / _  | | | | | |  |    // _ \| | | | __| |  _ \ / _ \
 | |/ / (_| | | | |_| |  | |\ \ (_) | |_| | |_| | | | |  __/
 |___/ \__ _|_|_|\__  |  \_| \_\___/ \__ _|\__|_|_| |_|\___|
                 __/ |                                     
                |___/                                      
    )"};
    stampaRigaPerRiga(testo, 0, 1);
    Sleep(1000);
    PlaySound(TEXT("./music/sorrow.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    print_slow(cout,"\nYou open your eyes again, It's morning, You are in your room like every day\nEverything around you is in it's right place\nThe memories of a dream that was better than reality fade away in your mind\nBut it's time to live now\nWhat do you do?\n\n1)Hop off bed.           2)Stay in.\n\n",50);
    cin>>ac;//1
    if(ac==1){
    print_slow(cout,"\nYou wake up and follow your usual routine,\nCoffee, Quick shower with shave,\nYou dress up in a way that makes you appreciate yourself,\nAnd just like that you are ready to crush the day\nYou exit your boring apartment and surf the streets\nWhat's the next move\n\n1)Go to work           2)Get around\n\n",55);
    cin>>xxx;
    if(xxx==1){//Scelta numero: 1.1
        print_slow(cout,"\nYou know what you gotta do,\nIf you don't go to work it's gonna be a problem for future you\nAnd you don't want that\nSo you take your car and go to work like every day\nOnce there, you greet your coworkers and go to your set-up\nThese gray walls make you feel a little dead inside\nYou don't even start working that you notice two SMS\nOne it's from a girl, She's really into you and you are too, She's asking if you want to go to dinner,\nThe other one is from your boss,\nHe wants to meet you ASAP,\nHe's not saying why tho so this does not make you hope for good\nBut you know you can only take one message\n\nWho will it be?\n\n1)Cute-girl.          2)Boss.\n\n",55);
        cin>>b;
        if(b==1){//Scelta numero: 1.1.1
            print_slow(cout,"\nYou don't wanna be rude to your boss, also if you don't really like him,\nBut sometimes it's better to prioritize personal life before business one,\nYou're not sure tho,\n\nWill you accept\n\n1)Accept.           2)Decline.\n\n",55);
            cin>>c;
            if(c==1){//Scelta numero: 1.1.1.1
                print_slow(cout,"\nThe answer seems kind of obvious,\nSince you like her it would make no sense to not go with her right?\nYou say -Sure, let's meet tonight, and propose a restaurant\nShe accepts right away\n'This is the right time' you think between yourself\nAs you keep working with a satisfied look on your face you wait for the work-day to end.\n\nFast forward a few hours,\nAfter work is done you come back to you car and found a rather not cool surprise\nYour car window on the driver side has been totally smashed\nNothing was even stolen since there was nothing valuable inside\nAnd if that didn't suck enough you hear a girl laugh in the distance of the parking lot\n",60);
                Sleep(100);
                print_slow(cout,"Who the fuck even was she\nAnyway you direct yourself home and park in the garage\nYou'll bring the car to the mechanic tomorrow, today you don't have time\nYou made it home at about 16 so you have plenty time\nYou go take a shower and watch some tv after\nTime fly's as usual, after getting dressed you're ready to hang out\nOn foot of course, it's almost sunset\nIn this time of the year it's pretty early\nIn about 20' you reach the place\nA classic italian restaurant, who doesn't like it?\nYou sit on a bench near by to wait for her, a little breeze is setting in\nIn about 5/6 minutes a girl who looks like her arrives,\n",60);
                Sleep(300);
                print_slow(cout,"\nAnd with that a thought also occurs your head\n",60);
                Sleep(840);
                SetConsoleTextAttribute(hc, 0x78);
                print_slow(cout,"\n-Shit this chick works at my place\n",40);
                Sleep(200);
                SetConsoleTextAttribute(hc, 0x70);
                print_slow(cout,"\nThis plus the fact she's kinda cute make you even more uncomfortable\nDo You wanna give it a shot?\n\n1)Meet Her         2)Ignore Her\n",60);
                cin>>ae;
                if(ae==1){//Scelta numero: 1.1.1.1.1
                    Sleep(400);
                    SetConsoleTextAttribute(hc, 0x78);
                    print_slow(cout,"\n-Hey are you Ashley?\n",40);
                    Sleep (500);
                    SetConsoleTextAttribute(hc, 0x74);
                    cout<<"\n-Yes, and you must be "<<nome<<endl;
                    //pausa da 500ms
                    Sleep (500);
                    SetConsoleTextAttribute(hc, 0x70);
                    print_slow(cout,"\nShe answers politely\n",60);
                    Sleep(500);
                    SetConsoleTextAttribute(hc, 0x78);
                    print_slow(cout,"\n-Yes that's me.\n",40);
                    Sleep(500);
                    SetConsoleTextAttribute(hc, 0x70);
                    print_slow(cout,"\nShe is wearing a white shift dress with long black pants,\nLong blond hair probably sunstrokes\nYou look into each other eyes for a few seconds\nAnd it's only when you are lost in her look that you remember\n",60);
                    SetConsoleTextAttribute(hc, 0x78);
                    print_slow(cout,"\n-Wait do we work in the same office?\n",40);
                    Sleep(500);
                    SetConsoleTextAttribute(hc, 0x70);
                    print_slow(cout,"\nShe giggles\n",60);
                    Sleep (500);
                    SetConsoleTextAttribute(hc, 0x74);
                    print_slow(cout,"\n-Yeah, Think i saw you a few times\n",40);
                    Sleep(500);
                    SetConsoleTextAttribute(hc, 0x70);
                    print_slow(cout,"\nA few funny look afterwards the waiter welcome and sits you\nYou order a Cheesesteak, She goes for something made out of salad, you didn't really understand\nAnd in a second you guys start talking like you are friends\n",55);
                    Sleep(500);
                    SetConsoleTextAttribute(hc, 0x78);
                    print_slow(cout,"\n-I have to break it down at the start,\n",38);
                    Sleep(500);
                    print_slow(cout,"-Do you do karate, saw some pictures on your account, the gym seems really similar to the one i used to go",36);
                    Sleep(500);
                    SetConsoleTextAttribute(hc, 0x74);
                    print_slow(cout,"\n-What an eye that you have,\n-Yeah i do a lot of karate, started late but ill'get to a black belt eventually\n",40);
                    Sleep(500);
                    SetConsoleTextAttribute(hc, 0x70);
                    print_slow(cout,"\nShe gives a determined look then sighs\nYou can tell from the shape she is in that she's been keeping herself trained while you kinda fell off\n",60);
                    SetConsoleTextAttribute(hc, 0x78);
                    print_slow(cout,"\n-The asskicker accountant",35);
                    SetConsoleTextAttribute(hc, 0x74);
                    Sleep(500);
                    print_slow(cout,"\n- SHUT UP-\n",30);
                    SetConsoleTextAttribute(hc, 0x70);
                    print_slow(cout,"\nShe shouts as you laugh, and this will be only one of the moments like this\nAs you eat your stupid meals you start debating\n",65);
                    Sleep(500);
                    SetConsoleTextAttribute(hc, 0x78);
                    print_slow(cout,"\n-What if we didn't need to eat?\n",35);
                    Sleep (500);
                    SetConsoleTextAttribute(hc, 0x74);
                    print_slow(cout,"-You kidding? That would be awesome, Like a thought less\n",35);
                    Sleep (500);
                    SetConsoleTextAttribute(hc, 0x78);
                    print_slow(cout,"-Yeah That's what im sayn' like so much cheap\n",34);
                    Sleep (500);
                    SetConsoleTextAttribute(hc, 0x70);
                    print_slow(cout,"\nAnd that went on...\n",60);
                    Sleep (500);
                    SetConsoleTextAttribute(hc, 0x78);
                    print_slow(cout,"\n-For how long could you walk like-\n",35);
                    Sleep(300);
                    SetConsoleTextAttribute(hc, 0x74);
                    print_slow(cout,"-OH, I Could walk the whole earth if i wanted to\n",30);
                    Sleep(200);
                    SetConsoleTextAttribute(hc, 0x78);
                    print_slow(cout,"-WHAT?\n",30);
                    Sleep(600);
                    SetConsoleTextAttribute(hc, 0x70);
                    print_slow(cout,"\n*Both Laugh*\n",10);
                    Sleep(500);
                    print_slow(cout,"It was about 0:27am that you realized  'holy shit, this girl is awesome'\nThat back and forth was going on for a few hours now\nAnd it was about 0:31am when she looked at her watch and went like:\n",60);
                    Sleep(500);
                    SetConsoleTextAttribute(hc, 0x74);
                    print_slow(cout,"\n-Holy shit that's so late, i gotta wake up tomorrow\n",70);
                    Sleep (500);
                    SetConsoleTextAttribute(hc, 0x78);
                    print_slow(cout,"-Yeah we wake up at the same time...\n",68);
                    SetConsoleTextAttribute(hc, 0x70);
                    print_slow(cout,"\nShe smiles in a funny way\nYou both stand up and go to the exit\nOnce outside you're eyes meet once again\nYou give each other a warm hug\n",60);
                    SetConsoleTextAttribute(hc, 0x74);
                    Sleep(400),
                    print_slow(cout,"\n-Wanna walk together?\n",38);
                    Sleep(200);
                    SetConsoleTextAttribute(hc, 0x70);
                    print_slow(cout,"She points to the direction where you came from\n",60);
                    SetConsoleTextAttribute(hc, 0x78);
                    Sleep(300);
                    print_slow(cout,"-Sure why not, since i've no car cause someone smashed my windows today..\n",38);
                    SetConsoleTextAttribute(hc, 0x74);
                    Sleep(500);
                    print_slow(cout,"-Mh, sorry to hear that...\n",36);
                    Sleep(1000);
                    print_slow(cout,"-Maybe they were warning you\n",36);
                    Sleep(1000);
                    SetConsoleTextAttribute(hc, 0x78);
                    print_slow(cout,"-About what?\n",42);
                    Sleep(1000);
                    SetConsoleTextAttribute(hc, 0x74);
                    print_slow(cout,"-I Don't know\n",38);
                    Sleep (300);
                    SetConsoleTextAttribute(hc, 0x70);
                    print_slow(cout,"\nShe smiles\nYou calmly walk her to her house\nYou have really enjoyed the night and not gonna lie, you really like her\n",60);
                    Sleep(2000);
                    SetConsoleTextAttribute(hc, 0x74);
                    cout<<"-We're arrived.\n";
                    SetConsoleTextAttribute(hc, 0x70);
                    print_slow(cout,"You look in her eyes for a second and give her a soft kiss on her lips\nShe blushes a little\n",60);
                    Sleep(1000);
                    SetConsoleTextAttribute(hc, 0x74);
                    print_slow(cout,"\n-Wanna come up?\n\n",58);
                    SetConsoleTextAttribute(hc, 0x70);
                    Sleep(400);
                    cout<<"1)Yes            2)Nah\n"<<endl;
                    cin>>ag;
                    if(ag==1){//Scelta numero: 1.1.1.1.1.1
                        SetConsoleTextAttribute(hc, 0x78);
                        print_slow(cout,"\n\n-Yeah that would be beautiful\n",45);
                        Sleep(500);
                        SetConsoleTextAttribute(hc, 0x70);
                        print_slow(cout,"You both smile cause you know what's gonna happen\nYou two are actually pretty\nThere is ton of feeling between you two\nYou arrive to her front door, 12th floor, wow she must be getting paid more than you\nHer place is lively, the living room is big, white walls and wooden forniture\nOh and a huge red soft carpet and couch\nShe has a lot of weird decoration that match the like samurai, kill bill aesthetic\nWhile you're admiring her DVD collection she locks the door behind you\nYou sit on the couch and she does too, you start kissing,\nThis alternation between kisses and looks full of love goes on for a bit\n",60);
                        Sleep(300);
                        SetConsoleTextAttribute(hc, 0x78);
                        print_slow(cout,"\n-I Really like you\n",40);
                        Sleep(500);
                        SetConsoleTextAttribute(hc, 0x70);
                        print_slow(cout,"\nYou yap, in this moment you remember how long has been since you went out with a girl\nYou feel almost weird about making out\nEspecially on a first date\nEspecially with a co-worker\n",60);
                        SetConsoleTextAttribute(hc, 0x74);
                        print_slow(cout,"\n-I Do too\n",38);
                        SetConsoleTextAttribute(hc, 0x70);
                        print_slow(cout,"\nShe says with love in her eyes\nYou start kissing her more and more until \n",60);
                        //bang suono
                        Sleep (1000);
                        print_slow(cout,"You hear a loud bang\nAshley immediately jumps on her feet, you lift your head to see\nSomeone blow up the door, There is a woman with a black suit in the living room\nShe has a weird blue gun.\n",42);
                        SetConsoleTextAttribute(hc, 0x78);
                        Sleep (500);
                        print_slow(cout,"\n-WHAT THE FUCK\n",28);
                        SetConsoleTextAttribute(hc, 0x70);
                        print_slow(cout,"\nAshley reach for a Katana on the wall\nThey start fighting\n",60);
                        SetConsoleTextAttribute(hc, 0x74);
                        Sleep (200);
                        cout<<"\n-"<<nome<<" YOU HAVE TO GET OUT\n";
                        Sleep(1000);
                        SetConsoleTextAttribute(hc, 0x72);
                        cout<<"\n-Oh bebe, "<<nome<<" will never be your's, he's not real enough\n";
                        SetConsoleTextAttribute(hc, 0x74);
                        Sleep (500);
                        print_slow(cout,"\n-LEAVE US ALONE\n",30);
                        SetConsoleTextAttribute(hc, 0x72);
                        Sleep (500);
                        print_slow(cout,"\n-Or maybe ill'game-end you two\n",45);
                        SetConsoleTextAttribute(hc, 0x70);
                        Sleep (500);
                        print_slow(cout,"\nAshley sprints to her to disarm her and she is actually successful to that due to her speed\nThe woman doesn't let that slip and responds with a kick to the face\nAshley doges that but in doing so falls on the flor which allows the woman to get onto her\n\nYou have so many question but Ashley is in real danger now and you feel like you have to do something\n\n1)Help her           2)Escape\n\n",60);
                        cin>>am;
                        if(am==1){//Scelta numero: 1.1.1.1.1.1.1
                            print_slow(cout,"\nYou take a katana weapon from the wall and run to her\nThat shit was made out of real metal\nYou didn't thought that these would have come in handy\nYou approach the girl from behind and slash her in the back\nThen in the neck, again\nThat does not seems to do much damage",60);
                            Sleep (500);
                            print_slow(cout,"\nAshley gets back up and reveals a knife hidden in a drawer\nShe kicks the woman back and pounces on her with the knife\nI join her too with whatever that weapon is\nWe don't know how much we go on\n",50);
                            Sleep (1000);
                            print_slow(cout,"\nSome tense minutes elapse, the only thing that goes on in the air are the sound of screams from the woman and the rage flawing from the mind trough the arms of both of us\nWhat a weird first date\nYou both look at each other and start laughing so hard like two crazy persons\nYou hugh covered in blood\nYou killed a person\n",60);
                            Sleep (1000);
                            print_slow(cout,"\nYou feel relief for a second, you both think you made it\nUntil something happens\nThe dead girl corpse starts ticking\nYou look into each other eyes\nKnowing exactly what is going to happen\nThere was a bomb in there\nWell at least you feel like you didn't commit any murder\nSince clearly that wasn't a human at 100%\n",60);
                            Sleep(500);
                            SetConsoleTextAttribute(hc, 0x74);
                            print_slow(cout,"\n-I love you\n",35);
                            Sleep(500);
                            SetConsoleTextAttribute(hc, 0x70);
                            print_slow(cout,"\nShe is sweet tho\n",60);
                            SetConsoleTextAttribute(hc, 0x78);
                            print_slow(cout,"\n-I love you too\n",35);
                            Sleep(500);
                            SetConsoleTextAttribute(hc, 0x70);
                            print_slow(cout,"\nThe two of you needlessly try running\nSeconds later, The Shockwave hits you\nThen the fire\nThen the fragments form the explosion\nThe loud bang strangely came for last, a loud whistle, then silence\nShe was the last thing i saw\nIn a second two lives were gone\nBut a second later",60);
                            Sleep (3500);
                            system("cls");
                            cambiaColoreSfondo(0,15);
                            for (int i = 0; i <= total; ++i) {
                            displayProgressBar(i, total);
                            std::this_thread::sleep_for(std::chrono::milliseconds(50));}
                            goto label2;
                        }
                        else(am==2);{//Scelta numero: 1.1.1.1.1.1.2
                            print_slow(cout,"\nYou sprint for the smoking front door, roll behind the fight and reach for the exit\nBut the run is cut short when a bullet hit your leg with a precise shot, Almost un-natural\nBut the second of distraction of the woman allowed Ashley to slide her neck with a knife\n",55);
                            SetConsoleTextAttribute(hc, 0x78);
                            cout<<"-That's f'd up\n";
                            Sleep(1000);
                            SetConsoleTextAttribute(hc, 0x74);
                            cout<<"Yh- Yeah.. it is\n";
                            Sleep(1000);
                            SetConsoleTextAttribute(hc, 0x78);
                            cout<<"-It Hurts so fucking much\n";
                            Sleep(400);
                            SetConsoleTextAttribute(hc, 0x70);
                            print_slow(cout,"You whisper as the poison from the bullet is slowly releasing in your body\nA subtle yet lethal way to kill\nThe last things you hear are screams, phone calls, syrens.\nNothing matters, at one point you closed your eyes, it felt like sleeping.\nEverything was terrible, but at the same time everything was so calm\nAnd in the exact moment you fell like falling in an infinite pit and about to touch the bottom, You feel a blinding light and -------------------------------------------------------",60);
                            cambiaColoreSfondo(0,15);
                            for (int i = 0; i <= total; ++i) {
                            displayProgressBar(i, total);
                            std::this_thread::sleep_for(std::chrono::milliseconds(50));}
                            goto label2;
                        }
                    }
                    else(ag==2);{//Scelta numero: 1.1.1.1.1.2
                        SetConsoleTextAttribute(hc, 0x78);
                        print_slow(cout,"\n-I would love to bae but i have to go play videogames",50);
                        Sleep(2000);
                        print_slow(cout,"...\n",70);
                        Sleep(1000);
                        SetConsoleTextAttribute(hc, 0x74);
                        print_slow(cout,"\n-Oh...",80);
                        Sleep(2000);
                        print_slow(cout," ok then ...\n-See you soon.\n",80);
                        SetConsoleTextAttribute(hc, 0x70);
                        print_slow(cout,"\nYou wave at her and walk home\nTurn on the pc and start grinding on the last mmo,\nYou farm for a few hours and then hop to bed.\n\nGood night!",60);
                        Sleep(5000);
                        system("cls");
                        cambiaColoreSfondo(0,15);
                        for (int i = 0; i <= total; ++i) {
                        displayProgressBar(i, total);
                        std::this_thread::sleep_for(std::chrono::milliseconds(50));}
                        Sleep(1000);
                        goto label2;
                    }
                }
                else(ae==2);{//Scelta numero: 1.1.1.1.2
                    print_slow(cout,"\nYou go down a fast train of thoughts about how bad it could go and arguably decide to leave,\nYou sneakly crawl to the opposite side of the street and go a few meters down\n",60);
                    Sleep(500);
                    print_slow(cout,"\nIt's a good moment to take your phone and text her\n",60);
                    SetConsoleTextAttribute(hc, 0x78);
                    print_slow(cout,"\n'Sorry for the last minute but i don't think ill'be able to make it'\n",30);
                    Sleep(500);
                    SetConsoleTextAttribute(hc, 0x70);
                    print_slow(cout,"\nAnd after that you shamelessly turn off your phone\nWalk a little bit more down the streets and go in the first bar that you find\n",60);
                    Sleep(300);
                    print_slow(cout,"\nInside there are few people and the place is not even well light up,\nYou sit at the counter shoulder to the exit\nNot much to say about the whole place either, empty other then the bar itself,\nSome alcohol behind the counter, the bartender in front of me looks sad as he dry's the glasses with a towel\nThere are also a few slot machines in the corner making some lights,\n",60);
                    SetConsoleTextAttribute(hc, 0x78);
                    Sleep(400);
                    print_slow(cout,"\n-WELL, looks like tonight is between us boys!\n",40);
                    Sleep(750);
                    SetConsoleTextAttribute(hc, 0x70);
                    print_slow(cout,"\nAfter that you just hear cough echoing trough the place\nNo one really vibes with you\nYou just exchange eye contact with the guy sitting besides you\n",60);
                    Sleep(750);
                    print_slow(cout,"\n1)Grab a drink           2)'Make some noise'\n",60);
                    cin>>qq;
                    if(qq==1){//Scelta numero: 1.1.1.1.2.1
                        //prendi il drink e quello accanto sono io e ti do la cartella iceberg lui parla di lenny
                    }
                    else(qq==2);{//Scelta numero: 1.1.1.1.1.2.2
                        //a bbudffo tiri fuiri le armi e pari alla gente fra cui ash, lenny ti ferma e torni al loop
                    }
                }
            }
            else(c==2);{//Scelta numero: 1.1.1.2
                print_slow(cout,"\nFor how much into her you can be\nYou don't really feel like going out with her\nSo you simply decide to make up an excuse and rethink asking your bro for a beer\n",60);
                Sleep(750);
                print_slow(cout,"\nSuddenly a weird sense of loneliness hits you\nThe incredibly loud sound of silence makes your head feel heavy\nNo one is interacting\nNo one is making memories\nIt almost feels like no one is growing older\nYou keep typing on your keyboard while time passes and nothing happens\nOnly one thing changes\nThe state of your bladder\n\n",60);
                Sleep(800);
                print_slow(cout,"You go to the rest room open the bathroom door\nA weird scene strikes you\n\nThere is a fairly short girl in front of you\nAs soon as she see's you she just sort of paralyze,\nShe's dressed in an unusual way for an office, all black, crop-top and some chains\nShe has a big gutting knife in her hand, A line of blood drips from her wrist on the floor\n\n1)Try to calm her down             2)Join her\n\n",60);
                cin>>n;
                if(n==1){//Scelta numero: //Scelta numero: 1.1.1.2.1
                SetConsoleTextAttribute(hc, 0x70);
                print_slow(cout,"\nYou stand in shock for a second, You inhale quickly and try to yap something out\n",60);
                SetConsoleTextAttribute(hc, 0x78);
                print_slow(cout,"\n-Hey there ... hm\n",80);
                SetConsoleTextAttribute(hc, 0x70);
                print_slow(cout,"\nYou whisper trying not to drag too much attention onto the situation\n",60);
                SetConsoleTextAttribute(hc, 0x78);
                print_slow(cout,"\n-Do you wanna talk a little before doing anything, you seem kind of cool.\n",75);
                SetConsoleTextAttribute(hc, 0x70);
                Sleep(1000);
                SetConsoleTextAttribute(hc, 0x75);
                print_slow(cout,"\n-Compliments won't help me,\n",45);
                SetConsoleTextAttribute(hc, 0x70);
                print_slow(cout,"\nFor the first time you hear her talking,\nHer voice feels raspy, like she's been smoking a lot lately\n",60);
                Sleep(500);
                SetConsoleTextAttribute(hc, 0x75);
                print_slow(cout,"\n-Talking won't help me ..\n",45);
                Sleep(600);
                SetConsoleTextAttribute(hc, 0x78);
                print_slow(cout,"\n-Ok, then what would help ya?\n",75);
                Sleep(400);
                SetConsoleTextAttribute(hc, 0x70);
                print_slow(cout,"\nAfter that she looks at you for a couple seconds with an expression between a surprised and a laugh\nHer stare feels like she's been going insane, she keeps looking at me immovable\nHer look starts to become more analytic, like she didn't saw a human in years\n",60);
                Sleep(300);
                SetConsoleTextAttribute(hc, 0x75);
                print_slow(cout,"\n-em..",45);
                Sleep(400);
                print_slow(cout," otions\n",45);
                SetConsoleTextAttribute(hc, 0x70);
                print_slow(cout,"\nAlltho intriguing this answer has no meaning to you\n",60);
                Sleep(400);
                SetConsoleTextAttribute(hc, 0x78);
                print_slow(cout,"\n-I don't exactly know what you mean but i think i can help you\n",50);
                SetConsoleTextAttribute(hc, 0x78);
                Sleep(350);
                SetConsoleTextAttribute(hc, 0x70);
                print_slow(cout,"\nHer stare lights up for a second, you swallow and go on\n",60);
                Sleep(350);
                SetConsoleTextAttribute(hc, 0x78);
                print_slow(cout,"\n-You know, i've spent a lot of time alone in my life, and therefore i spent a lot of time just with my emotions ... ",50);
                Sleep(200);
                print_slow(cout,"i write a lot about em'\n",50);
                Sleep(300);
                SetConsoleTextAttribute(hc, 0x70);
                Sleep(400);
                print_slow(cout,"\nShe's still looking at you in a way of disbelief,\nShe start laughing almost in relief\nShe come close to you and rest her head on your chest, gently grabbing your shirt in a sort of hug.\nA small black tear falls onto your shirt leaving a stain\nYou feel a strong bond in that hug, like it's from two people in a long distance relationship meeting for the first time\nYou try not to lose yourself in your fantasies and keep your composure\nShe looks into your eyes from under your chin,\nShe gently presses the tip of the knife she was about to use on herself on your stomach\n",60);
                Sleep(600);
                SetConsoleTextAttribute(hc, 0x75);
                print_slow(cout,"\n-Ok then, show me what you know.\n",50);
                SetConsoleTextAttribute(hc, 0x70);
                Sleep(400);
                print_slow(cout,"\nAnd again, the world puts you in weird situations,\nBut this time is even more serious then what you wanted to be\n\n1)End what you started          2)Renounce\n\n",60);
                cin>>af;
                if(af==1){//Scelta numero: 1.1.1.2.1.1
                    SetConsoleTextAttribute(hc, 0x78);
                    print_slow(cout,"\n-Oh yes yes ill'show ya\n",50);
                    SetConsoleTextAttribute(hc, 0x70);
                    print_slow(cout,"\nYou take your phone out the poket and look for a pdf,\nOnce found you show it to her\n",60);
                    Sleep(1100);
                    system("start https://drive.google.com/file/d/1GtOfwSTsWmEdFigRJD-vIW3gilXKNlFr/view?usp=drive_link");
                    Sleep(15000);
                    print_slow(cout,"\nAs soon as she starts reading her expression becomes more and more diverged\nA bunch of seconds later she's done reading\n",60);
                    Sleep(100);
                    print_slow(cout,"And she burst out laughing.\n",60);
                    SetConsoleTextAttribute(hc, 0x75);
                    print_slow(cout,"-HAHAHAH AND YOUR WROTE THIS?!\n",35);
                    Sleep(230);
                    print_slow(cout,"-IT LOOKS FROM A 10 YEARS OLD HAHAHAHAH\n",35);
                    Sleep(100);
                    SetConsoleTextAttribute(hc, 0x70);
                    print_slow(cout,"\nYou feel disappointed for a second,\nYes, surely not one of your best works\nBut that reaction was just eccessive\n",60);
                    Sleep(150);
                    SetConsoleTextAttribute(hc, 0x78);
                    print_slow(cout,"\n-C'mon don't do me like that\n",45);
                    SetConsoleTextAttribute(hc, 0x70);
                    print_slow(cout,"\nYou say cracking a smile\n",60);
                    Sleep(100);
                    SetConsoleTextAttribute(hc, 0x75);
                    print_slow(cout,"\n-OoOoOo shit-",30);
                    Sleep(200);
                    print_slow(cout,"   jesus sorry gotta catch a smoke.",35);
                    Sleep(100);
                    SetConsoleTextAttribute(hc, 0x70);
                    print_slow(cout,"And just like that she leaves the room\nClassic mood-swings you see in a depressed person\nWell at least even if the note was shitty you",60);
                    Sleep(200);
                    print_slow(cout," ...",100);
                    print_slow(cout,"made her feel ",60);
                    Sleep(50);
                    print_slow(cout,"emotions\n",100);
                    Sleep(100);
                    print_slow(cout,"You take your deserved piss and go wash your hands,\nThis still resonates in you a little, sure first time happening\nYou take a second to make yourself up and catch a breath,\nYou walk up to the corridor,",60);
                    Sleep(80);
                    print_slow(cout," you feel a little dizzy\nAn idea passes your mind\nYou really wouldn't mind the joint you kept for all this time in your desk drawer\nOr do you?\n\n1)Hit         2)Pass\n",60);
                    cin>>jj;
                    if(jj==1){//Scelta numero: 1.1.1.2.1.1.1
                        Sleep(120);
                        print_slow(cout,"\nYou reach for your desk and open the drawer\nBut no joint was there, instead\n",60);
                        Sleep(1500);
                        system("start https://drive.google.com/file/d/18c3CWgEmicNokyPvt-Vd8_jNpmPLRoVb/view?usp=drive_link");
                        Sleep(10000);
                        print_slow(cout,"\nWhat the hell is that supposed to mean?\nYou try to think about when you could have met her\nBut the thought in your head is like unable to propreply form\nInstead all the days and people just fade in a blurred spiral of memories\nIf before you wanted that joint now you are craving it\nYou rush out to the open balcony of the office\nAnd sure enough she's there, smoking your joint\n",60);
                        Sleep(120);
                        SetConsoleTextAttribute(hc, 0x78);
                        print_slow(cout,"\n-Didn't they teach you stealing is a little disrespectful\n",47);
                        SetConsoleTextAttribute(hc, 0x70);
                        print_slow(cout,"\n-Oh cry me a river. ",38);
                        Sleep(200);
                        print_slow(cout,"you have no clue how much i need this more then you do\n",48);
                        Sleep(100);
                        print_slow(cout,"... or maybe not ehehe",45);
                        SetConsoleTextAttribute(hc, 0x70);
                        Sleep(150);
                        print_slow(cout,"She says as she hands you the joint she had been smoking\nThere is something deeply troubled about this girl\nShe acts like she knows me almost, hope she's not been stalking\nShould i stay at her game?\n\n1)Yes         2)Nope\n",60);
                        cin>>gg;
                        if(gg==1){//Scelta numero: 1.1.1.2.1.1.1.1
                            SetConsoleTextAttribute(hc, 0x70);
                            print_slow(cout,"\nYou grab the joint as you look her in the eyes\nYou wanna know more\n",60);
                            SetConsoleTextAttribute(hc, 0x78);
                            Sleep(200);
                            print_slow(cout,"\n-Indeed not ",45);
                            Sleep(100);
                            print_slow(cout,"...you can't know what i could have seen ok?",40);
                            Sleep(150);
                            print_slow(cout,"\n-The fucked up things i had to remain silent about.\n",40);
                            Sleep(125);
                            print_slow(cout,"-Back in that bathroom, it could have easily been me if i wasn't strong enough\n",40);
                            Sleep(200);
                            print_slow(cout,"-The regret never goes away, you just grow around it.\n",50);
                            Sleep(1000);
                            SetConsoleTextAttribute(hc, 0x75);
                            print_slow(cout,"\n-yadeyade i already knew that\n-i don't even feel regret but thanks for the words\n",32);
                            Sleep(250);
                            //daifinire
                        }
                        else(gg==2);{//Scelta numero: 1.1.1.2.1.1.1.2

                        }
                    }
                    else(jj==2);{//Scelta numero: 1.1.1.2.1.1.2
                        //linea temporale in cui si muore frate falla senza senso ti prego
                    }
                }
                else(af==2);{//Scelta numero: 1.1.1.2.1.2
                    Sleep(500);
                    PlaySound(TEXT("./music/UVCLP.wav"), NULL, SND_FILENAME | SND_ASYNC );
                    print_slow(cout,"\nYou look at her and get infected by her sadness,\nAll your hopes fade away\nIt's a slow process,\nYou feel it coming slowly like a trip",60);
                    Sleep(500);
                    SetConsoleTextAttribute(hc, 0x70);
                    print_slow(cout,"\nThis time giving up doesn't feel bad,\nThis time with her beside you it feels ... normal, human\nYou feel understood\n",50);
                    SetConsoleTextAttribute(hc, 0x70);
                    Sleep(600);
                    print_slow(cout,"\nThis time you feel comfortable with all the things you ever did wrong,\nAll the mistakes made along the way\nThe things you broke, the people you've hurt\nIt doesn't matter in the end\nNo life will metter when one day there will be none",60);
                    Sleep(500);
                    SetConsoleTextAttribute(hc, 0x75);
                    print_slow(cout,"\n-You don't wanna talk huh?\n",60);
                    Sleep(750);
                    SetConsoleTextAttribute(hc, 0x78);
                    print_slow(cout,"\nYou shake your head,\nYou feel almost embarrassed like you want to cry\nBut you are learning something\nFeels like the first time doing so\n",50);
                    Sleep(500);
                    SetConsoleTextAttribute(hc, 0x70);
                    print_slow(cout,"\nBut you just understood that death is not a bad thing\nIt makes us appreciate life more\nIt makes us move, instead of staying in bed\nIt makes us think instead of rot\nIt makes us more real somehow\n",60);
                    Sleep(500);
                    SetConsoleTextAttribute(hc, 0x75);
                    print_slow(cout,"\n-You could have just joined me, idiot\n",40);
                    Sleep(300);
                    SetConsoleTextAttribute(hc, 0x78);
                    print_slow(cout,"\n-You have got to fail to understand a loser.\n",60);
                    Sleep(1000);
                    SetConsoleTextAttribute(hc, 0x75);
                    print_slow(cout,"\n-We are not that different after all ",50);
                    cout<<nome;
                    Sleep(1000);
                    SetConsoleTextAttribute(hc, 0x78);
                    print_slow(cout,"\nYou smile and nod to the girl\nShe's cleaning her knife blade on her clothes to be shiny again,\nIs she still going to do it\n",60);
                    Sleep(500);
                    SetConsoleTextAttribute(hc, 0x70);
                    print_slow(cout,"\nYou suddenly violently hug her\nYou're careful to not hurt her,\nShe freezes for a second, you try to hold everything in\nYou hear her breathing a little uncontrollably\nShe leaves the grip on the knife\n",70);
                    Sleep(1000);
                    print_slow(cout,"\nIt doesn't budge, stuck in your stomach\nYou smile, this doesn't feel like dying\nIt feels beautiful, like fixing something broken\nAbandoning all fears behind, a rebirth\n",50);
                    Sleep(500);
                    print_slow(cout,"\nThe girl grabs the knife back and pulls it out\nIt hurts, you fall\nShe comes on top of you silently\nShe blots the wound a little then she comes closer to hug you back.\nShe's warm\n",55);
                    SetConsoleTextAttribute(hc, 0x75);
                    print_slow(cout,"\n-ow you dummy\n-at least you learned something\n-you're so cute when you die y'know\n-but you always come back don't you\n",40);
                    SetConsoleTextAttribute(hc, 0x70);
                    print_slow(cout,"\nYou instinctively push her back\nWhat does she knows?\nWhat does she really mean?\nSo much blood is coming out of your wound",60);
                    Sleep(1000);
                    SetConsoleTextAttribute(hc, 0x75);
                    print_slow(cout,"\n-well we'll see tomorrow i guess\n",40);
                    SetConsoleTextAttribute(hc, 0x70);
                    print_slow(cout,"\nShe says smiling\nWith the knife still in her hands she comes closer again\nShe stabs you another two times in the torso,\nEnough to make you pass out from the pain",60);
                    cambiaColoreSfondo(0,15);
                    system("cls");
                    print_slow(cout,"\nYou were still breathing and throwing up blood for a few minutes after\nThe girl just left you there\nYou don't know what happened after\nYou only know that everything was dark and cold for time\n\nThen           Light\n",60);
                    Sleep(500);
                    system("cls");
                    for (int i = 0; i <= total; ++i) {
                    displayProgressBar(i, total);
                    std::this_thread::sleep_for(std::chrono::milliseconds(50));}
                    goto label2;
                }
                }
                else(n==2);{//Scelta numero: 1.1.1.2.2
                    print_slow(cout,"\nYou look at her in the eyes for a second that seem to last way more, you say:\n",60);
                    SetConsoleTextAttribute(hc, 0x78);
                    print_slow(cout,"\n-Don't worry you don't have to say anything, i thought about doing it in here too\n",50);
                    SetConsoleTextAttribute(hc, 0x70);
                    print_slow(cout,"\nShe cracks a smile\nYou look at her with a somewhat serious glance\n",60);
                    SetConsoleTextAttribute(hc, 0x78);
                    print_slow(cout,"\n-Listen i don't really know you but...\n",50);
                    SetConsoleTextAttribute(hc, 0x70);
                    print_slow(cout,"\nYou take a pause\nYou don't know how long, time seems to be passing in 0.5 in there\n",60);
                    SetConsoleTextAttribute(hc, 0x78);
                    print_slow(cout,"\n-I really don't like my life either in a pretty long time\n",55);
                    SetConsoleTextAttribute(hc, 0x70);
                    print_slow(cout,"\nYou say while taking out a small knife from your jacket\n",60);
                    SetConsoleTextAttribute(hc, 0x78);
                    print_slow(cout,"\n-Im tired, can i join you?\n",55);
                    SetConsoleTextAttribute(hc, 0x70);
                    print_slow(cout,"She come close to you, looks you deeply in the eyes and kisses you on the mouth\nThat mix of unexpected and weird situation almost turns you on\n",50);
                    SetConsoleTextAttribute(hc, 0x75);
                    print_slow(cout,"\n-Mh ye you could join me\n",60);
                    Sleep(1200);
                    print_slow(cout," . . . \n",100);
                    Sleep(1200);
                    print_slow(cout,"-Or maybe we could help each other..\n",55);
                    SetConsoleTextAttribute(hc, 0x70);
                    Sleep(2500);
                    print_slow(cout,"\nShe says while she slips an hand in your pocket where the knife was before leaving the bathroom\nIt's a business card\n",60);
                    system("start https://drive.google.com/file/d/1O9jk6UsWhP6OwhHU69WtQVrNANYI0CLF/view?usp=drive_link");
                    Sleep(8000);
                    print_slow(cout,"'Alice Kyeler' and some infos\nFound some to do tonight huh\nYou piss and get back to your desk\nLittle time till the work day is done\n\n1)Work              2)Go back home\n\n",60);
                    cin>>o;
                    if(o==1){//Scelta numero: 1.1.1.2.2.1
                        PlaySound(TEXT("./music/LYETDWTS.wav"), NULL, SND_FILENAME | SND_ASYNC);
                        print_slow(cout,"\nAnd so you keep working\n\n1)Work            2)Keep working\n\n",60);
                        cin>>q;
                        Sleep(750);
                        print_slow(cout,"\nAnd so you keep working\n",60);
                        Sleep(1200);
                        print_slow(cout,"\nAnd so you keep working\nAnd so you keep working\nAnd so you keep working And so you keep workingAnd so you keep working And so you keep working\nAnd so you keep working And so you keep workingAnd so you keep working And so you keep working\nAnd so you keep working And so you keep workingAnd so you keep working And so you keep working\n",40);
                        Sleep(4500);
                        cout<<"\nAnd so you keep working\n";
                        Sleep (1500);
                        cout<<"And so you keep working\n";
                        Sleep (1000);
                        cout<<"And so you keep working\n";
                        Sleep (1000);
                        cout<<"And so you keep working\n";
                        Sleep (1000);
                        cout<<"And so you keep working\n";
                        Sleep (1000);
                        cout<<"And so you keep working\n";
                        Sleep (500);
                        cout<<"And so you keep working\n";
                        Sleep (500);
                        cout<<"And so you keep working\n";
                        Sleep (500);
                        cout<<"And so you keep working\n";
                        Sleep (500);
                        cout<<"And so you keep working\n";
                        Sleep (500);
                        cout<<"And so you keep working\n";
                        Sleep (500);
                        cout<<"And so you keep working\n";
                        Sleep (500);
                        cout<<"And so you keep working\n";
                        Sleep (100);
                        cout<<"And so you keep working\n";
                        Sleep (100);
                        cout<<"And so you keep working\n";
                        Sleep (100);
                        cout<<"And so you keep working\n";
                        Sleep (100);
                        cout<<"And so you keep working\n";
                        Sleep (100);
                        cout<<"And so you keep working\n";
                        Sleep (100);
                        cout<<"And so you keep working\nAnd so you keep working\nAnd so you keep working\nAnd so you keep working\nAnd so you keep working\nAnd so you keep working\nAnd so you keep working\nAnd so you keep working\nAnd so you keep working\nAnd so you keep working\nAnd so you keep working\nAnd so you keep working\nAnd so you keep working\nAnd so you keep working\nAnd so you keep working\nAnd so you keep working\n";
                        system("cls");
                        cambiaColoreSfondo(0,15);
                        Sleep(7500);
                        print_slow(cout,"\nYou wake up on your desk with the PC still on",60);
                        Sleep(750);
                        print_slow(cout,"\nIt's 3:33am\nYou feel lost at first like you are in a dream\nYou realize this was definitely the worst sleep of your life\nThen you remember what you missed on, Alice...",60);
                        Sleep(750);
                        print_slow(cout,"\nYour view si still a little blurry but you remember about her\n",60);
                        Sleep(500);
                        print_slow(cout,"You decide to go on the roof to assaporate a little of the night breeze\nYou take the elevator to the R floor\nThe usual mirror in it reminds you of how borderline you are\nBut it also reminds you of ... her\n",60);
                        Sleep(750);
                        SetConsoleTextAttribute(hc, 0x78);
                        print_slow(cout,"\n-fuck, i need to get her off my head\n-we exchanged information, i'll call her.\n",40);
                        Sleep(750);
                        print_slow(cout,"\nYour legs feels heavy during the rise\nThe silence makes you hear everything\nThe electricity going trough the muted speakers\nThe weight pulling the elevator up and the cabin surfing the wire\nAnd then it stops\nAnd the door opens\n",60);
                        system("cls");
                        cambiaColoreSfondo(1,15);
                        Sleep(1200);
                        print_slow(cout,"You walk out almost surprised to see the roof\nYou basically never come here\nYou walk calmly to the balcony\nIt's so late time, time feels so relative\nMind as well take it easy\nYou lean a bit against the fence with your back\nYou take a second to breath\n",60);
                        Sleep(2000);
                        print_slow(cout,"   ...\n",60);
                        SetConsoleTextAttribute(hc, 0x18);
                        print_slow(cout,"\n-Ok, i'll call her.\n",45);
                        Sleep(750);
                        print_slow(cout,"\nYou take your phone out your pocket and dial her number\n",60);
                        Sleep(5000);
                        print_slow(cout,"\n No one picks up\nAgain, the same\nYou start getting anxious\nShe must have done it\nYou feel like you've fucking killed her\nYou look down the roof\n17th floor\nEnough to transform your body in a bunch of guts spread over the sidewalk\nYour brain goes silent for a second\n\n1)Jump             2)Go home\n\n",60);
                        cin>>r;
                        if(r==1){//Scelta numero: 1.1.1.2.2.1.1
                            print_slow(cout,"You stare down\nYou feel your heart beating really strong\nThoughts are clouded\nYou are step away for the edge\nFrom death\nYou look to the moon\nIt's always been a symbol to you\nOf the goals you wanted to reach\nSo visible but so far at the same time\nYou step forward with your eyes closed\n\n",60);
                            Sleep(5000);
                            print_slow(cout,"But death never comes\nYou open your eyes back\n",60);
                            Sleep(2000);
                            print_slow(cout,"\nYou are one step away form the ground\nFreezed in mid-air\nIn front of you there is a person that at fist scares the shit out of you\nIt's a woman dressed in a black work suite\n",60);
                            SetConsoleTextAttribute(hc, 0x7a);
                            print_slow(cout,"\n-What were you trying to do?\n",80);
                            SetConsoleTextAttribute(hc, 0x70);
                            print_slow(cout,"\nShe holds her hand to you\nYou grab it and rest your feet on the ground safely\n\n",60);
                            Sleep(800);
                            SetConsoleTextAttribute(hc, 0x7a);
                            print_slow(cout,"-Im sorry but, death is not an option, at least not the one that we intended for you..\n",50);
                            Sleep(400);
                            SetConsoleTextAttribute(hc, 0x70);
                            print_slow(cout,"You don't even have the time to process to ask what the fuck she's talking about that...",60);
                            Sleep(3000);
                            system("cls");
                            cambiaColoreSfondo(0,15);
                             for (int i = 0; i <= total; ++i) {
                            displayProgressBar(i, total);
                            std::this_thread::sleep_for(std::chrono::milliseconds(50));}
                            Sleep(200);
                            goto label2;
                        }
                        else(r==2);{//Scelta numero: 1.1.1.2.2.1.2
                            print_slow(cout,"\nYou look down and back off\nYou don't wanna die already\nTake the elevator for the ground floor\nWhile the floor passes you look at your reflection in the mirror\nYou don't look that good, your hair are messy\nYou look tired, you have rings under your eyes\nOnce at the ground floor you think it's a good idea to walk home instead of driving\nReception is empty, shame, Pam would have been the only one capable to bring your emotions back up\nYou walk home alone in the coldness of the night\nYou feel a little empty after today,\nWhat if that girl really killed herself?\nI mean you could have been friends\nYou could have taught her what you learned\nAll the things that you know about emotions, that instead just live into your four walls\nYou could have made it trough\nTogather maybe\n",60);
                            Sleep(500);
                            SetConsoleTextAttribute(hc, 0x78);
                            print_slow(cout,"\n-Ppfffff..\n",48);
                            Sleep(500);
                            SetConsoleTextAttribute(hc, 0x70);
                            print_slow(cout,"\nYou also feel kind of bad for how you treated Ashley\nBut now if you try asking her out, she's probably gonna decline\n",60);
                            Sleep(500);
                            print_slow(cout,"\nWhile lost in the train of thoughts,\nYou see a person at the end of the sidewalk under a light pole\nJust a few meters before your condo\nIt's just standing there, feels kind of weird but you will have to walk past it,\n",60);
                            Sleep(500);
                            print_slow(cout,"\nYou take a breath and speed up your walk as you walk past it\nShe seems a female figure, dressed with a black work suit\nReally elegant for someone just wondering the night\nAs you were about to pass her, you hear her talking\n",60);
                            Sleep(500);
                            SetConsoleTextAttribute(hc, 0x72);
                            print_slow(cout,"\n-Hey ",90);
                            cout<<nome;
                            print_slow(cout," we need to talk\n",90);
                            Sleep(500);
                            SetConsoleTextAttribute(hc, 0x70);
                            print_slow(cout,"\nAlso if she knew my name, i never saw this woman in my life\nBut she seemed really polite\nHer voice is so candid and clean and soft\nIt almost feels hypnotic, you answer her\n",60);
                            SetConsoleTextAttribute(hc, 0x78);
                            print_slow(cout,"\n-Do tell me ma'am",50);
                            Sleep(500);
                            SetConsoleTextAttribute(hc, 0x72);
                            print_slow(cout,"\n-We saw you've been running in circles lately\n",80);
                            SetConsoleTextAttribute(hc, 0x70);
                            Sleep(500);
                            print_slow(cout,"\nYou give her a confused smirk,\nBut she probably can't see cause it seems like she's looking at the ground trough the sun glasses\nShe goes on:\n",60);
                            Sleep(500);
                            SetConsoleTextAttribute(hc, 0x72);
                            print_slow(cout,"\n-And from what i've read, that's not really your thing\n",80);
                            Sleep(500);
                            SetConsoleTextAttribute(hc, 0x70);
                            print_slow(cout,"\nRead? what does she mean by that?\nThis person is getting really creepy really fast\n",60);
                            Sleep(500);
                            SetConsoleTextAttribute(hc, 0x78);
                            print_slow(cout,"\n-Hey who the hell are you, what are you talking about?\n",46);
                            Sleep(500);
                            SetConsoleTextAttribute(hc, 0x70);
                            print_slow(cout,"\nShe lowers her sunglasses just enough for you to see portion of her black eyes\n",60);
                            SetConsoleTextAttribute(hc, 0x72);
                            Sleep(500);
                            print_slow(cout,"\n-Me?",78);
                            Sleep(550);
                            print_slow(cout," ...\n",100);
                            Sleep(500);
                            print_slow(cout,"-I am the leader of the sheep\n-I am the blood stain on a white shirt\n-I am a gun in a medieval war\n",68);
                            Sleep(500);
                            print_slow(cout,"-I am ",70);
                            Sleep(500);
                            print_slow(cout,"the handshake with the devil\n",80);
                            Sleep(150);
                            SetFontSize(22);
                            SetFontSize(24);
                            SetConsoleTextAttribute(hc, 0x70);
                            print_slow(cout,"\nYou honestly don't understand\nYou are too sleepy you could be imagining things\n",60);
                            SetFontSize(22);
                            SetFontSize(24);
                            Sleep(400);
                            SetConsoleTextAttribute(hc, 0x78);
                            print_slow(cout,"\n-Ok girl i have to go now\n",50);
                            Sleep(500);
                            SetConsoleTextAttribute(hc, 0x72);
                            print_slow(cout,"\n-Wait\n",45);
                            Sleep(500);
                            SetConsoleTextAttribute(hc, 0x70);
                            print_slow(cout,"\nShe quickly grabs you by the hand\nHer grip is really tight,\nShe goes on with her dialogue\n",60);
                            Sleep(500);
                            SetConsoleTextAttribute(hc, 0x72);
                            print_slow(cout,"\n-You have to stop doing useless stuff like this\n-Not everything is lite and funny as it seems\n-Get to the bottom of it\n",65);
                            Sleep(500);
                            SetConsoleTextAttribute(hc, 0x70);
                            print_slow(cout,"\nYou lost it, this girl talks in metaphors\nBut for the little you have understand you are still pretty in shock\nWhy does it seem like she knows so much about you even tho you never met her\nThis feels weird, this is weird\n",60);
                            Sleep(500);
                            SetConsoleTextAttribute(hc, 0x78);
                            print_slow(cout,"\n-Can i go?",45);
                            Sleep(100);
                            SetConsoleTextAttribute(hc, 0x72);
                            print_slow(cout,"\n-Yes, one last thing,",70);
                            Sleep(200);
                            print_slow(cout," don't be stupid and try to fight me.\n",40);
                            SetConsoleTextAttribute(hc, 0x70);
                            print_slow(cout,"\nIn a rapid movement she takes both of her hands and puts them on your temples\nThen she puts both of her thumbs in the middle of your forehead\nYou don't even have time to ask yourself what she's doing\nThat she pushes really hard with her thumbs\nFor a fraction of a second a sharp pain hits you in that spot\nLike a needle went trough there\nYou try to move around but your body is not responding at your inputs anymore,\n",40);
                            Sleep(750);
                            print_slow(cout,"Slowly your eyelids slide close",60);
                            Sleep(500);
                            system("cls");
                            cambiaColoreSfondo(0,15);
                            Sleep(2500);
                            SetConsoleTextAttribute(hc, 0x02);
                            print_slow(cout,"\n-",75);//dainserirefrase e hint
                            Sleep(400);
                            system("cls");
                            cambiaColoreSfondo(0,15);
                            for (int i = 0; i <= total; ++i) {
                            displayProgressBar(i, total);
                            std::this_thread::sleep_for(std::chrono::milliseconds(50));}
                            goto label2;
                        }
                    }
                    else(o==2);{//Scelta numero: 1.1.1.2.2.2
                        print_slow(cout,"\nWhile you drive back you still can't stop thinking about her\nThat was so surreal but ironic at the same time\nYou eat dinner at home while watching Youtube, usual depression meal\nYou rest and play some games, but you know what you are actually waiting for\nYou're passing her whatever card between your fingers\nShould you call her?\n\n1)Call           2)Don't\n\n",60);
                        cin>>p;
                        if(p==1){//Scelta numero: 1.1.1.2.2.2.1
                            print_slow(cout,"\nYou type the number on your phone,\nAfter a few rings she pick up the line\n\n . . .\n",60);
                            SetConsoleTextAttribute(hc, 0x75);
                            print_slow(cout,"\n-Hello\n",80);
                            Sleep(300);
                            SetConsoleTextAttribute(hc, 0x78);
                            print_slow(cout,"\n-Hey Alice\n",80);
                            SetConsoleTextAttribute(hc, 0x70);
                            print_slow(cout,"\n1)",60);
                            SetConsoleTextAttribute(hc, 0x78);
                            print_slow(cout,"-Why were you killing yourself?            ",60);
                            print_slow(cout,"2)",60);
                            SetConsoleTextAttribute(hc, 0x78);
                            print_slow(cout,"-LeT's pLaY ViDeOgAmEs\n\n",45);
                            SetConsoleTextAttribute(hc, 0x70);
                            cin>>al;
                            if(al==1){//Scelta numero: 1.1.1.2.2.2.1.1
                                //alice si stupisce e poi si apre un po'
                                //dafinire
                            }
                            else(al==2);{//Scelta numero: 1.1.1.2.2.2.1.2
                                print_slow(cout,"\nYou try to elaborate something, pretending you know how to talk to a woman\nBut you ended up in the comfort zone as always, you said something like:\n",60);
                                SetConsoleTextAttribute(hc, 0x78);
                                print_slow(cout,"\n-Wanna hop on something, do you have discord, any chance??\n",80);
                                SetConsoleTextAttribute(hc, 0x75);
                                print_slow(cout,"\n-Hmm, sure weirdo\n",80);
                                SetConsoleTextAttribute(hc, 0x70);
                                print_slow(cout,"*She laughs*\n",60);
                                SetConsoleTextAttribute(hc, 0x75);
                                print_slow(cout,"-What game are you on?\n",80);
                                SetConsoleTextAttribute(hc, 0x78);
                                print_slow(cout,"\n-Uhm i wanted to play Valorant tonight\n",30);
                                SetConsoleTextAttribute(hc, 0x75);
                                print_slow(cout,"\n-YOU'RE SO EDGY, WHO DO YOU THINK I AM?!\n",25);
                                Sleep(2000);
                                SetConsoleTextAttribute(hc, 0x78);
                                print_slow(cout,"\n-I . . .\n",20);
                                SetConsoleTextAttribute(hc, 0x75);
                                print_slow(cout,"\n-With that being said, i might be on tonight\n",40);
                                SetConsoleTextAttribute(hc, 0x78);
                                print_slow(cout,"\n-You might huh\n",40);
                                SetConsoleTextAttribute(hc, 0x70);
                                Sleep(1000);
                                print_slow(cout,"*Both chuckle*",60);
                                SetConsoleTextAttribute(hc, 0x75);
                                print_slow(cout,"\n-Ok so mi discord is ******69\n",30);
                                SetConsoleTextAttribute(hc, 0x78);
                                print_slow(cout,"\n-Cool hear you in a sec.\n",30);
                                Sleep(1500);
                                SetConsoleTextAttribute(hc, 0x7C);
                                cout<<"\n****************CALL ENDED****************\n";
                                SetConsoleTextAttribute(hc, 0x70);
                                Sleep(1000);
                                print_slow(cout,"\nNot even a second passes after you realize\nShe's pretty chill after all\nYou send her a friend request, She accepts it right away\nYou join a common server and start playing some Valorant\nShe's pretty neat\nTime flies, you play also some multiplayer games\nThe ones you buy to play for one night and then drop forever\nIn the meantime you also manage to talk a little about yourselves\nShe mentions she's like into magic stuff or something\nBut at one point she hits you with the:\n",60);
                                SetConsoleTextAttribute(hc, 0x75);
                                print_slow(cout,"\n-Ok baby that was my last one\nSee you tomorrow at work\n",40);
                                Sleep(1000);
                                SetConsoleTextAttribute(hc, 0x70);
                                print_slow(cout,"\nHonestly for something that started from nothing, you feel pretty ok\nShe's a fun girl, plus she plays videogames so win win\nYou feel like this can be the start of something fun\nMaybe a good friendship who knows\nYou decide to hop in bed and see what will happen tomorrow\nCause every day it's a new discovery\n\nYou close your eyes.",50);
                                Sleep(1500);
                                system("cls");
                                cambiaColoreSfondo(0,15);
                                Sleep(500);
                                for (int i = 0; i <= total; ++i) {
                                displayProgressBar(i, total);
                                std::this_thread::sleep_for(std::chrono::milliseconds(50));}
                                goto label2;
                            }
                        }
                        else(p==2);{//Scelta numero: 1.1.1.2.2.2.2

                        }
                    }
                }
            }
        }
        else(b==2);{//Scelta numero: 1.1.2
            print_slow(cout,"\nFor how much you could like her, You know it's unwise to not answer your boss\nSo you pick up the phone and say 'aigth im coming'\nGo up a few floors and knock a few times\nHe's there sitting at his desk in front of you\nHe welcomes you with a sad nod and starts talking with his hoarse voice\nHe yaps for a bit and then that line hits you like a knife in the chest\n",60);
            Sleep(500);
            SetConsoleTextAttribute(hc, 0xCF);
            print_slow(cout,"\n-I Think we'll have to fire you",40);
            Sleep(500);
            SetConsoleTextAttribute(hc, 0x70);
            print_slow(cout,"\n\nYou're not that surprised, You haven't been really productive lately\nBut that does not stop your brain to get blurry and filled with rage\n\n1)Keep it.           2)Express it.\n\n",60);
            cin>>g;
            if(g==1){//Scelta numero: 1.1.2.1
                print_slow(cout,"\nYou swallow the pill and try to even force a smile out of your lips\n",55);
                Sleep(500);
                SetConsoleTextAttribute(hc, 0x78);
                print_slow(cout,"\n-ok\n",80);
                Sleep(500);
                SetConsoleTextAttribute(hc, 0x70);
                print_slow(cout,"\nYou mumble before leaving the room\nYou go back to your desk for the last moments to take your stuff\nAs you fill the box with useless junk the desk phone rings\nThat phone is actually yours, you brought it from an old house to here so you should take it back with you logically\n",60);
                Sleep(500);
                SetConsoleTextAttribute(hc, 0x78);
                print_slow(cout,"\n-Wait what the fuck\n",50);
                SetConsoleTextAttribute(hc, 0x70);
                Sleep(500);
                print_slow(cout,"\nYou say as you notice that you already unplugged it\nThen why the fuck is it ringing?\n\n1)Pick it up            2)Let it ring\n\n",55);
                cin>>l;
                if(l==1){//Scelta numero: 1.1.2.1.1
                    label4: print_slow(cout,"\n\nYou're kinda weirded out but you still grab the cornet\nA surprisingly crystal clear voice of a woman speaks form the other side\n",60);
                    Sleep(500);
                    SetConsoleTextAttribute(hc, 0x72);
                    print_slow(cout,"\n-Hey uuh we don't have a lot of time, You are making the right choices Compliments for that\nNow in order to be successful .. You see Mathew's Computer over there?\n",35);
                    Sleep(1000);
                    SetConsoleTextAttribute(hc, 0x70);
                    print_slow(cout,"\nYou turn and actually notice Mathew,\nA coworker you really don't have a lot of confidence with working at the desk beside you\nThat's not even his usual place\n",60);
                    Sleep(1500);
                    SetConsoleTextAttribute(hc, 0x72);
                    print_slow(cout,"\n-There is a folder there called `Hyperplane`, you have to take it from his pc and bring it to us,\nDon't be too suspicious, and remember\n\n",35);
                    Sleep(1500);
                    print_slow(cout,"-We didn't chose you, you chose us.\n",65);
                    Sleep(1500);
                    SetConsoleTextAttribute(hc, 0x7C);
                    cout<<"\n****************CALL ENDED****************\n";
                    Sleep(800);
                    SetConsoleTextAttribute(hc, 0x78);
                    print_slow(cout,"\n-What the..\n",50);
                    SetConsoleTextAttribute(hc, 0x70);
                    print_slow(cout,"\nYou are intrigued but scared at the same time\nYou look at Mathew and gulp\nSo you approach him\n",55);
                    SetConsoleTextAttribute(hc, 0x78);
                    cout<<"\n-hey mat what's up?\n";
                    Sleep(1000);
                    SetConsoleTextAttribute(hc, 0x70);
                    cout<<"\n1)Can you get me a coffee?           2)Take the laptop and run\n\n";
                    cin>>aa;
                    if(aa==1){//Scelta numero: 1.1.2.1.1.1
                        Sleep(500);
                        SetConsoleTextAttribute(hc, 0x78);
                        print_slow(cout,"\n-how is life?\n",40);
                        Sleep(500);
                        SetConsoleTextAttribute(hc, 0x73);
                        print_slow(cout,"\n-mh hey, all good, how about you?\n",40);
                        Sleep(500);
                        SetConsoleTextAttribute(hc, 0x78);
                        print_slow(cout,"\n-all right man, Listen they just fired me can we talk for a second?\n",40);
                        Sleep(500);
                        SetConsoleTextAttribute(hc, 0x73);
                        print_slow(cout,"\n-oh yeah sure, wow, uhm tell me\n",40);
                        Sleep(500);
                        SetConsoleTextAttribute(hc, 0x78);
                        print_slow(cout,"\n-you'know i paly videogames right, tonight i have a huge ride on wow\n-Like one in a milion years right?\n-It's probably gonna take like 8 hours or so\n-And since now im broke i won't be able to afford coffee\n-And ill'p-\n",30);
                        SetConsoleTextAttribute(hc, 0x73);
                        print_slow(cout,"-are you asking for coffee?\n",40);
                        Sleep(1500);
                        SetConsoleTextAttribute(hc, 0x78);
                        print_slow(cout,"\n-yeah, you got it\n",55);
                        Sleep(400);
                        SetConsoleTextAttribute(hc, 0x73);
                        print_slow(cout,"-ok, sure whatever, im rich\n",50);
                        Sleep(500);
                        SetConsoleTextAttribute(hc, 0x78);
                        print_slow(cout,"-cocky\n",40);
                        Sleep(500);
                        SetConsoleTextAttribute(hc, 0x70);
                        print_slow(cout,"\nAnd so he goes\nThe PC is there, unlocked\nWhat a moron\nYou open file explorer and search around for a bit and eventually find the folder\nYou grab your USB and drag and drop `Hyperplane` in it\n\n",55);
                        for (int i = 0; i <= total; ++i) {
                        displayProgressBar(i, total);
                        std::this_thread::sleep_for(std::chrono::milliseconds(15));}
                        print_slow(cout,"\n\nSuddenly, The phone rings again, This time is your personal one tho\n'unknown caller'\nYou answer thinking you already know who is calling\n",55);
                        Sleep(1000);
                        SetConsoleTextAttribute(hc, 0x78);
                        print_slow(cout,"\n-Yo\n",80);
                        SetConsoleTextAttribute(hc, 0x72);
                        Sleep(500);
                        print_slow(cout,"\n-Did you open it?\n",35);
                        Sleep(1000);
                        SetConsoleTextAttribute(hc, 0x78);
                        print_slow(cout,"\n-No?\n",80);
                        Sleep(1000);
                        SetConsoleTextAttribute(hc, 0x72);
                        print_slow(cout,"\n-Open it and look at it, when you're done you better get moving\n-Maybe you'll realize the weight of what you put yourself into\n",35);
                        Sleep(1500);
                        SetConsoleTextAttribute(hc, 0x78);
                        cout<<"\n-ok?\n";
                        Sleep(1000);
                        SetConsoleTextAttribute(hc, 0x7C);
                        cout<<"\n****************CALL ENDED****************\n";
                        Sleep(500);
                        SetConsoleTextAttribute(hc, 0x70);
                        print_slow(cout,"\nAll of this confuses you, who is that girl?\nYou flee the scene not caring about Matthew at all, Direct yourself to the first empty set-up you see\nTurn on the PC and open up the folder\nYou'll take a minute to make sure to check it properly\n",60);
                        system("start https://drive.google.com/file/d/18WsCxK5ysRKCzL19FnLPN819lQqkyJaP/view?usp=drive_link");//Cartella da capire cosa mettere
                        Sleep(60000);
                        SetConsoleTextAttribute(hc, 0x78);
                        print_slow(cout,"\n-Ok, they seem just like scattered words...",60);
                        Sleep(500);
                        SetConsoleTextAttribute(hc, 0x70);
                        print_slow(cout,"\nYou also noticed what seems to be coordinates, think that's where they wanna lead you next\nYou stand from the PC and leave everything there, Who even cares at this point\nYou rush to the elevator, the short ride makes you feel a bit fuzzy\nThe coordinates seem to locate a spot near a river few minutes outside of town\nNo prob ill'just drive there, But first your boss asked to leve your badge at the reception\n",55);
                        Sleep(2000);
                        print_slow(cout,"You exit the elevator and walk to the reception\nPam is there doing nothing as usual",60);
                        print_slow(cout,"\nYou have a pretty good relationship with her so it's kinda embracing to tell her you got fired\n",60);
                        Sleep(1000);
                        SetConsoleTextAttribute(hc, 0x7E);
                        print_slow(cout,"\n-Heyy ",50);
                        cout<<nome;
                        print_slow(cout," what is up?\n",50);
                        SetConsoleTextAttribute(hc, 0x78);
                        print_slow(cout,"\n-Oh you know the usual other then a few weird phone calls\n",50);
                        Sleep(2000);
                        print_slow(cout,"-Oh and i just got fired so here's my badge\n",50);
                        Sleep(800);
                        SetConsoleTextAttribute(hc, 0x7E);
                        print_slow(cout,"-Oh im so sorry to hear that\n",50);
                        Sleep(500);
                        SetConsoleTextAttribute(hc, 0x78);
                        print_slow(cout,"\n-Nah it's ok i wanted to change job, see you around Pam.\n",50);
                        SetConsoleTextAttribute(hc, 0x7E);
                        print_slow(cout,"\n-Sure, see you\n",50);
                        Sleep(1500);
                        SetConsoleTextAttribute(hc, 0x70);
                        print_slow(cout,"\nYou walk away form Pam's desk and outside of the building\nAt the moment you really have nothing better to do\nAnd having these coordinates makes you feel a little less lost\nYou still can't make up to yourself how weird this is\nBut at the same time you've always been a fan of these kind treasure hunts\nBut why should i be the one to have choose to partecipate\nYou arrive to the car",60);
                        Sleep(1200);
                        print_slow(cout,"\nOnly to find it all scratched on the side\n",60);
                        SetConsoleTextAttribute(hc, 0x78);
                        print_slow(cout,"\n-WHAT THE HELL MAN I JUST GOT THE PAINT JOB DONE\n",30);
                        Sleep(1000);
                        SetConsoleTextAttribute(hc, 0x70);
                        print_slow(cout,"\nOn the right door there are apparent white scratches since your car is black,\nSome of theme are just random lines,\nOther ones looks like a bad drawing of eyes\nYou also notice a little pice of paper all folded up sitting on the sidewalk right beside the driver seat\n\n1)Investigate scratches                2)Pick up note\n\n",60);
                        cin>>ah;
                        if(ah==1){//Scelta numero: 1.1.2.1.1.1.2
                            SetConsoleTextAttribute(hc, 0x78);
                            print_slow(cout,"\n-This is unacceptable, i paid way too much\n",30);
                            SetConsoleTextAttribute(hc, 0x70);
                            print_slow(cout,"\nYou go back inside the office building and approach Pam once again\n",60);
                            Sleep(1000);
                            SetConsoleTextAttribute(hc, 0x78);
                            print_slow(cout,"-Hey pam sorry to bother you again, can you check the parking security camera for me?\n",40);
                            Sleep(800);
                            SetConsoleTextAttribute(hc, 0x7E);
                            print_slow(cout,"\n-Sure",40);
                            cout<<nome;
                            print_slow(cout,"for what reason?\n",40);
                            Sleep(800);
                            SetConsoleTextAttribute(hc, 0x78);
                            print_slow(cout,"\n-So um   i went to my car just to find it all scratched up so..\n",40);
                            Sleep(800);
                            SetConsoleTextAttribute(hc, 0x7E);
                            print_slow(cout,"\n-Oh my,   really sounds like it's not your day\n",40);
                            SetConsoleTextAttribute(hc, 0x78);
                            print_slow(cout,"\n-Yeah...\n",40);
                            Sleep(1200);
                            SetConsoleTextAttribute(hc, 0x70);
                            print_slow(cout,"\nShe opens up the footage, around 9am that is when everybody clocks in\nEverything is pretty chill until she fast forwards at around 11am\n\nThere you both see, just in the upper corner of the recording what looks like to be a girl\nShe's white and dressed in a total black outfit with a crop-top and chains\n\nIn the video she walks back and forth your car presumably scratching it\nAs soon as you see that scene your rage kind of fades away\nYou also think that you really don't care about pressing charges\nPlus her face is not really visible in the footage\n\n",60);
                            Sleep(500);
                            print_slow(cout,"You say thanks to Pam and once again return to your car\nThe note is gone, probably the wind carried it away\nYou start driving to the coordinates, it's a calm ride that makes you reflect on the current situation\nYou don't know what expect, you don't feel that a lot in this life made of monotony\nYou park your car and walk to the river\n\nThe coordinates point right in front of you\nYou look around for a second and just feel the wind on your face\nThis place is beautiful you've never been here before\nYou walk just a few steps ahead just to notice a weird pile of rocks near a bush\nWeird since there are really no rocks around at all\n\n1)Search the rocks            2)Rest near the river\n\n",60);
                            cin>>an;
                            if(an==1){//Scelta numero: 1.1.2.1.1.1.1
                                //dafinire
                            }
                            else(an==2);{

                            }
                        }
                        else(ah==2);{//Scelta numero: 1.1.2.1.1.1.1
                            PlaySound(TEXT("./music/AYN.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
                            print_slow(cout,"\nYou knee and pick up the note\n",60);
                            system("start https://drive.google.com/file/d/1D141GhkYAfl57cyhiuDskDCovsvk6KnV/view?usp=drive_link");
                            Sleep(60000);
                            print_slow(cout,"\nThis makes you a little bit uneasy\nThat handwriting too, it's weird\n\nIt's just ",60);
                            Sleep(500);
                            print_slow(cout,"sad.\n",80);
                            Sleep(500);
                            print_slow(cout,"\nAnyway you store the letter away safely in your pocket\n",60);//dafinire

                        }
                    }
                    else(aa==2);{//Scelta numero: 1.1.2.1.1.2
                        print_slow(cout,"\nYou stare at him for a sec\nNot a single thought in your mind\nHe his on his phone, you stand up,The laptop is on the side of the desk\nAs you pass near it you silently grab it\nIt does not take long for him to notice it and start screaming\n\n",60);
                        SetConsoleTextAttribute(hc, 0x73);
                        print_slow(cout,"\n-Hey man what the fuck?\n",37);
                        SetConsoleTextAttribute(hc, 0x70);
                        print_slow(cout,"\nYou start running trough the office stalls\nYour heart rate start raising as soon you realize everybody is looking at you\nYou go trough a few other rooms and soon realize you can't run in circles\n\n1)Hide in the bathroom           2)Go down the stairs\n\n",45);
                        cin>>ak;
                        if(ak==1){//Scelta numero: 1.1.2.1.1.2.1
                            print_slow(cout,"\n\nYou turn towards the bathrooms and enter the man one\nYou see few coworkers washing their hands, familiar faces\nYou enter the toilet room and lock the door behind you\n",50);
                            Sleep(1000);
                            print_slow(cout,"\nYou sit on the toilet and open the laptop\n",60);
                            SetConsoleTextAttribute(hc, 0x78);
                            Sleep(250);
                            print_slow(cout,"\n-Shit Shit Shit\n",35);
                            Sleep(1000);
                            SetConsoleTextAttribute(hc, 0x70);
                            print_slow(cout,"\nIt's locked\nNo big deal, You have a friend that can unlock it in seconds\nYou just need to get out of here,\nSo you unclock the door back and get out but\n",57);
                            PlaySound(TEXT("./music/Opencar.wav"), NULL, SND_FILENAME | SND_ASYNC );
                            Sleep(780);
                            print_slow(cout,"\nIn front of you there is mathew, with him your boss\nThey're both staring at you\nMathew goes",60);//dafini
                            Sleep(500);
                            SetConsoleTextAttribute(hc, 0x70);
                            //dafinire
                        }
                        else(ak==2);{//Scelta numero: 1.1.2.1.1.2.2

                        }
                    }
                }
                else(l==2);{//Scelta numero: 1.1.2.1.2
                    print_slow(cout,"\nThe phone keeps ringing and ringing\nYou let it until it's done\nAs soon as it stops you feel a really strong headache\nYour view gets dark for a second like you just got iron deficiency\nThen in the distance you hear another phone\nThen another\nAnd another\nIt gets to a point where you think that all the phones in the office are ringing\nYou feel like your ears are bleeding\n\n1)Pick up             2)Break them\n\n",55);
                    cin>>ab;
                    if(ab==1){//Scelta numero: 1.1.2.1.2.1
                        goto label4;
                    }
                    else(ab==2);{//Scelta numero: 1.1.2.1.2.2
                        SetConsoleTextAttribute(hc, 0x70);
                        print_slow(cout,"\nYou feel like going insane, you grab your phone and throw it on the wall,\nThat does not stop all the other ones form ringing\nYou're sick of it, You leave the place\nYou use the stair to be quicker\nBut once at the fifth floor something catches your attention for a second\nIt's a perfect copy of the 'Venus de Milo'\n\n",55);
                        system("start https://drive.google.com/file/d/1lZ-Kqg9t_R5fMbOd0MtaeMTmjLquZ_cM/view?usp=drive_link");
                        Sleep(6500);
                        print_slow(cout,"What the fuck was it doing here?\nThat's so similar plus you have been really obsessed with it lately\nIt's such a good pice of art why is it here laying in an old office\nI don't know but weird things are happening today in here\n",60);
                        Sleep(1000);
                        print_slow(cout,"You go a little closer to it thinking it's a replica\nYou start knocking a bit on it with your finger\nIt feels heavy, not full tho, this might still be marble\nStanding close to it it's actually much taller than you\nThere is no way this is actually the original,\nBeing close to it you hear a weird noise,\nYou put your hear near to it.\n",60);
                        PlaySound(TEXT("./music/BO.wav"), NULL, SND_ASYNC);
                        //daggiunfgerecanzone
                        Sleep(8000);
                        print_slow(cout,"\nThat sure is weird\n\n1)Go away          2)Push the statue\n\n",60);
                        cin>>aq;
                        if(aq==1){//Scelta numero: 1.1.2.1.2.2.1
                            print_slow(cout,"\nYou don't wanna get into more trouble",60);//dafinire
                        }
                        else(aq==2);{//Scelta numero: 1.1.2.1.2.2.2
                            print_slow(cout,"\nYou get one last good look out of it\nA shame the france has it\nThey first take art from the italians\nAnd then place it in a burning crumbling museum\nAnyway you go to it's back and give it a push with your hands\n",60);
                            //dafninire
                        }
                    }
                }
            }
            else(g==2);{//Scelta numero: 1.1.2.2
                PlaySound(TEXT("./music/DOGMATICA.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
                print_slow(cout,"\nThe frustration of the whole month flows through you blood and makes it boil\nYour boss is there in front of you looking directly in your eyes\nAlmost smiling\nYou look back at him and laugh\nYou start picking up random objects form his desk and trowing them at him\nSeeing the stapler hitting his forehead was so satisfying\nUntil, blinded by rage you accidentally throw the paper cutter, directly at his face\n",60);
                Sleep(750);
                print_slow(cout,"\nYou hit his eye\nHe starts bleeding, your blood goes cold\nHe starts screaming too\nThe comfort of the anger is gone, and you're just left in a mess you caused\nHow will you escape that?\n\n1)'Go postal'            2)Get out\n\n",55);
                cin>>m;
                if(m==1){//Scelta numero: 1.1.2.2.1
                    print_slow(cout,"\nYou're into it too deep, the mess won't fix itself\nAnd when someone else is gonna 'take care of it' it will only mean to arrest you\nYou stand up\n",60);
                    Sleep(500);
                    SetConsoleTextAttribute(hc, 0x78);
                    print_slow(cout,"\n-You see boss, before wasting half my time in this place\n",55);
                    Sleep(750);
                    print_slow(cout,"-I had projects,\n-Dreams, i was social, hanged out, had friends\n-All that shattered by this fucking job\n",40);
                    Sleep(750);
                    SetConsoleTextAttribute(hc, 0x70);
                    print_slow(cout,"\nHe looks at you in disbelief for a moment\nHe's holding his bleeding nose with his hands\nThe blood is dripping from his hands onto the desk\n",60);
                    Sleep(750);
                    print_slow(cout,"\nWhile talking you've walked near a gray locker, unlocked\nOn it there is a sign that says ",60);
                    SetConsoleTextAttribute(hc, 0x7C);
                    print_slow(cout," 'to use in case of emergency'\n",60);
                    SetConsoleTextAttribute(hc, 0x70);
                    Sleep(500);
                    print_slow(cout,"\nYou know everything about this place\nSo well that you don't need to know, to know\nYou brutally open the locker making the whole think shake",60);
                    Sleep(750);
                    print_slow(cout,"\nInside there is a gun, a browning hp\nYou pull the magazine, it's full\nYou're still looking inside the locker, stretch your arm and shoot your boss\nYou then aim and see you hit him in his shoulder while he was paralyzed on his chair\nHe starts screaming loudly, you panic\n",60);
                    Sleep(120);
                    SetConsoleTextAttribute(hc, 0x78);
                    print_slow(cout,"\n-Shut the fuck up will ya?\n",35);
                    SetConsoleTextAttribute(hc, 0x70);
                    print_slow(cout,"\nHe of curse doesn't\nIndeed he screams louder\nCalling for help this time\n",60);
                    Sleep(750);
                    print_slow(cout,"\nYour mind is going numb\nThere's only two options\n\n1)Kill him            2)Kill yourself\n\n",60);
                    cin>>as;
                    if(as==1){//Scelta numero: 1.1.2.2.1.1
                        //dafinire
                    }
                    else(as==2);{//Scelta numero: 1.1.2.2.1.2
                        print_slow(cout,"\n\nYour heart beats out of your chest,\nYou've never been in such a situation\nYou feel trapped by this office\nYou don't want to come out of it anymore\nMaybe hell won't be so cruel if you don't bring someone with you\nYou put the pistol barrel and press the trigger\n",60);
                        system("cls");
                        Sleep(750);
                        cambiaColoreSfondo(12, 15);
                        Sleep(60);
                        PlaySound(NULL, NULL, 0);
                        cambiaColoreSfondo(0,15);
                        Sleep(500);
                        for (int i = 0; i <= total; ++i) {
                        displayProgressBar(i, total);
                        std::this_thread::sleep_for(std::chrono::milliseconds(50));}
                        cambiaColoreSfondo(7,0);
                        PlaySound(TEXT("./music/piedi.wav"), NULL, SND_FILENAME | SND_ASYNC);
                        std::vector<std::string> testo = {R"(
                        ______      _ _         ______            _   _            
                        |  _  \    (_) |        | ___ \          | | (_)           
                        | | | |__ _ _| |_   _   | |_/ /___  _   _| |_ _ _ __   ___ 
                        | | | / _  | | | | | |  |    // _ \| | | | __| |  _ \ / _ \
                        | |/ / (_| | | | |_| |  | |\ \ (_) | |_| | |_| | | | |  __/
                        |___/ \__ _|_|_|\__  |  \_| \_\___/ \__ _|\__|_|_| |_|\___|
                                        __/ |                                     
                                       |___/                                      
                        )"};
                        stampaRigaPerRiga(testo, 0, 1);
                        Sleep(1000);
                        PlaySound(TEXT("./music/sorrow.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
                        print_slow(cout,"\nYou open your eyes again, It's morning, You are in your room like every day\nEverything around you is in it's right place\nThe memories of a dream that was...",50);
                        Sleep(750);
                        print_slow(cout," vivid\nYou remember your office\nYou doing some fucked up shit\nYou ",60);
                        Sleep(500);
                        print_slow(cout,"still feel pain form shooting yourself\nWhat is going on why is this so real",60);
                        cambiaColoreSfondo(0,7);
                        Sleep(100);
                        cambiaColoreSfondo(7,0);
                        print_slow(cout,"\nYou stand up from the bed\nThat can't be a dream, it felt too real\nYou start connecting a few dots and question reality\nAs if you did't normally did it\nBut this was a lot weirder, i mean you feel like being stuck in a loop when you only work\nBut being literally stuck in a time loop is insane\n",60);
                        //dafinire
                    }
                }
                else(m==2);{//Scelta numero: 1.1.2.2.2
                    print_slow(cout,"\nHe's there, laying on the floor\nYou quickly check for his vital signs on his neck\nHe's thankfully alive, maybe not too well tho\n",60);
                    Sleep(1300);
                    SetConsoleTextAttribute(hc, 0x78);
                    print_slow(cout,"\n-Hey man get better\n",40);
                    Sleep(1000);
                    SetConsoleTextAttribute(hc, 0x70);
                    print_slow(cout,"\nYou say while you leave the room\nWhen did you get so cold?\nYou probably can't even answer that yourself\nYou leave the building without taking anything back\nDon't really care about all these objects\nAs soon as you are out\nYou feel like you have a lot of energy in you\nSo you start running\nAnd running\nAfter a lot of meters tho\nYou bump into a girl, and make her fall on the ground\nAll of her notes she was holding are sent flying in the air\nYou almost fall too\nYou stop for a sec\n\n1)Help her get up          2)Keep running\n\n",60);
                    cin>>u;
                    if(u==1){//Scelta numero: 1.1.2.2.2.1
                        SetConsoleTextAttribute(hc, 0x78);
                        print_slow(cout,"\n-Fuck im so sorry, are you ok?\n",40);
                        Sleep(1500);
                        SetConsoleTextAttribute(hc, 0x70);
                        print_slow(cout,"\nYou say while hold out your hand to her\n",60);
                        Sleep(1000);
                        SetConsoleTextAttribute(hc, 0x72);
                        cout<<"\n-Yeah, yeah im good\n";
                        Sleep(1200);
                        SetConsoleTextAttribute(hc, 0x70);
                        print_slow(cout,"\nShe says while holding your hand to stand up\nYou quickly grasp the notes, your heart is beating out of your chest\nYou aren't really used to exercise lately\nWhile you grab the notes you see a few interesting things\nUnder a category called 'The chosen one's' there are photos of few men\nThere is a picture of yourself\n\n1)Keep walking            2)Ask about it\n\n",55);
                        cin>>v;
                        if(v==1){//Scelta numero: 1.1.2.2.2.1.1
                            print_slow(cout,"\nYou give her the notes back\n",60);
                            SetConsoleTextAttribute(hc, 0x78);
                            cout<<"\n-Sorry again miss\n";
                            print_slow(cout,"\nYou nod at her and leve\nShe stayed silent the whole time\nBut before you turn around, she points to the direction from witch she was coming\n",60);
                            Sleep(1000);
                            SetConsoleTextAttribute(hc, 0x78);
                            print_slow(cout,"\n-Ook miss\n",40);
                            SetConsoleTextAttribute(hc, 0x70);
                            Sleep(1000);
                            print_slow(cout,"\nThen she turn too and start walking the opposite direction\n",60);
                            SetConsoleTextAttribute(hc, 0x78);
                            Sleep(500);
                            print_slow(cout,"\n-What a weird girl\n",45);
                            Sleep(1000);
                            SetConsoleTextAttribute(hc, 0x70);
                            print_slow(cout,"\nYou start walking normally again and seeing the world for what it is\nIt's hard to accept the firing but it's fine you're young and still can do whatever\nYou didn't even liked that job at all, just pam\nAnd that encounter with the woman almost made you forget it already\nNow that i think about it why did she point in the end? ... to what?\nThere is basically nothing in this area other than workspaces, cars, and",60);
                            Sleep(750);
                            print_slow(cout," a sad phone cabin\n\nIt's a normal phone cabin\nPretty dirty too\nWith graffiti all over the exterior\nYou keep walking your way wandering what to do next\nBut as soon as you walk past the cabin the phone starts ringing\nThese things can riceve call too?\nYou never used one so you really don't actually know\n\n1)Pick it up             2)Let it ring\n\n",55);
                            cin>>z;
                            if(z==1){//Scelta numero: 1.1.2.2.2.1.1.1
                                Sleep(750);
                                SetConsoleTextAttribute(hc, 0x78);
                                print_slow(cout,"\n-Hello\n",50);
                                SetConsoleTextAttribute(hc, 0x75);
                                print_slow(cout,"\n-ARE YOU FUCKING BLIND SHE'S GOING AROUND JUST WALKING\n-SHE'S NEVER DONE THAT LIKE EVER\n",30);
                                Sleep(500);
                                SetConsoleTextAttribute(hc, 0x78);
                                print_slow(cout,"\n-Excuse me who is this?\n",40);
                                SetConsoleTextAttribute(hc, 0x75);
                                print_slow(cout,"\n-SEE WHERE SHE GOES YOU IDIOT\n",35);
                                SetConsoleTextAttribute(hc, 0x78);
                                print_slow(cout,"\n-COUGH COUGH EUGH PFF BLEAH\n",30);
                                Sleep(100);
                                SetConsoleTextAttribute(hc, 0x7C);
                                cout<<"\n****************CALL ENDED****************\n";
                                Sleep(1000);
                                SetConsoleTextAttribute(hc, 0x70);
                                print_slow(cout,"\nPutting that phone close to your mouth was a mistake\nNobody used that in ages, it was covered in dust and spier webs\nYou've got some in your mouth, ew\n",60);
                                Sleep(1500);
                                SetConsoleTextAttribute(hc, 0x78);
                                print_slow(cout,"\n-Ok i mean let's get going\n",35);
                                Sleep(750);
                                SetConsoleTextAttribute(hc, 0x70);
                                print_slow(cout,"\nYou spit on the sidewalk and trace back the woman steps\nYou can still see her in the distance, she hasn't turn yet",60);
                                //dafinire
                            }
                            else(z==2);{//Scelta numero: 1.1.2.2.2.1.1.2

                            }
                        }
                        else(v==2);{//Scelta numero: 1.1.2.2.2.1.2
                            print_slow(cout,"\nYou look at the picture for a few more seconds\nYup that's you\n",60);
                            SetConsoleTextAttribute(hc, 0x78);
                            Sleep(1200);
                            print_slow(cout,"\n-Im sorry miss, what the fuck is this?\n",40);
                            Sleep(1200);
                            SetConsoleTextAttribute(hc, 0x70);
                            print_slow(cout,"\nWhile you say that you notice her weird fit\nShe's dressed in a total black working suite and black sunglasses\nShe does not say anything\n",60);
                            Sleep(1200);
                            SetConsoleTextAttribute(hc, 0x78);
                            print_slow(cout,"\n-MA'AM WHAT IS THIS\n",40);
                            Sleep(1200);
                            SetConsoleTextAttribute(hc, 0x70);
                            print_slow(cout,"\nShe takes the note form your hand, crumples it and tosses it away\nThen she takes her phone out\n an old vintage 80'style phone with a long antenna\n",60);
                            Sleep(1200);
                            SetConsoleTextAttribute(hc, 0x72);
                            print_slow(cout,"\n-Guys, take me out, something happened that shouldn't have.\n",50);
                            Sleep (3500);
                            system("cls");
                            cambiaColoreSfondo(0,15);
                            Sleep(500);
                            for (int i = 0; i <= total; ++i) {
                            displayProgressBar(i, total);
                            std::this_thread::sleep_for(std::chrono::milliseconds(50));}
                            goto label2;
                        }
                    }
                    else(u==2);{//Scelta numero:1.1.2.2.2.2
                        SetConsoleTextAttribute(hc, 0x70);
                        print_slow(cout,"\nYou don't even care anymore\nYou straight up laugh, at this point it's just funny\nThe poor girl trips and fall as the wind plays with your tie\nSomeone screams, but you keep running\nYou feel somewhat alive\n",55);
                        print_slow(cout,"You run crossing a red light, a car honks at you\nYou feel so out of place doing this in the middle of  the city but it's also so relieving\nYou keep running towards north for a bit when you realize your about to pass in front of the working place of a friend\n\n",45);
                        cout<<"1)Keep running           2)Stop by\n\n";
                        cin>>w;
                        if(w==1){//Scelta numero: 1.1.2.2.2.2.1
                            print_slow(cout,"\nDon't care at all, your steps on the ground never felt so good\nThe sun is shining and you feel like breathing for the first time\nThis is so much fun, You see the environment changing around you\nYou start running quicker\n",43);
                            print_slow(cout,"You see all the faces of the people for a split second\nYou really don't know what to do next without a job\nYou just want to enjoy the moment\nThe dream becomes even more real when you realize you're basically out of town\nThe main color surrounding you now has became the yellow of all the dry grass of the camps around the road\nThe sidewalk ends there, is only a gray road with patches of wheat to the sides\n\n",37);
                            cout<<"1)Keep running           2)Stop\n\n";
                            cin>>aj;
                            if(aj==1){//Scelta numero: 1.1.2.2.2.2.1.1
                                print_slow(cout,"\nYou run and run in the middle of the road\nYou're not even sweating,\n",35);
                                print_slow(cout,"Funny how sometimes your brain decides to release random chemicals\nThe fact that your dressed so well makes it even funnier\nSome cars honk at you, you laugh at them\n",22);
                                print_slow(cout,"A guy screams 'Hey Forest Gump get the fuck out'\nYour heart is asking you to stop\nBut your mind is telling you to keep going\n",20);
                                print_slow(cout,"And so you do\nAs your mind fills with so much useless thoughts that make you giggle sometimes\nBut you are still focussed with the run\nYou keep running\n",17);
                                print_slow(cout,"You're going fast, really fast,\nfast as fuck boy, you feel like in a cartoon\nBut sill enjoy it, you don't feel tired\nYou just keep burning your legs\nUntil you get to a point of non-return\nIn front of you the road was over and just left a overhang",15);
                                print_slow(cout,"\nYou try stopping but it's too late, you fall in this pit, it's orange like a kenyon,\nIt's deep, around 35m\nSurely enough to kill you, you close your eyes and wait for your death\nYou go down meter by meter,\n'So far so good' You keep repeating in your head\nYou open your eyes back just to see that you're still falling\nInside of the earth trough the terrain\nIt's like the ground was just a pass trough texture without foundation\nThis can't be real, this is impossibile\nThat's why i wasn't feeling tired\nThis is why there is an open unfinished road in the middle of people This is not real.\n",10);
                                Sleep(2000);
                                print_slow(cout,"\nYou close your eyes again\n",60);
                                system("cls");
                                cambiaColoreSfondo(0,0);
                                Sleep(1500);
                                cambiaColoreSfondo(15,0);
                                print_slow(cout,"\nThen",80);
                                Sleep(600);
                                print_slow(cout," you open your eyes to a blinding white\nYour bottom half feels heavy, you're submerged in water\nIn every direction, for as far as the eye can stretch there was water\nYou were falling in the sea\nIt's weirdly warm and comforting\n",60);
                                Sleep(1000);
                                SetConsoleTextAttribute(hc, 0xF8);
                                print_slow(cout,"\n-Maybe i should have stopped...\n",50);
                                Sleep(500);
                                SetConsoleTextAttribute(hc, 0xF0);
                                print_slow(cout,"\nYou whisper, your body feels good,\nYou're still missing some air from the run and the warmness of the water not allowing you to inhale properly\n",60);
                                Sleep(500);
                                print_slow(cout,"\nYou start swimming around\nClothes tighten on you making it hard to move well\nYou are really good at swimming but the question still is\n",60);
                                Sleep(500);
                                print_slow(cout,"\nTo where?\n",100);
                                Sleep(500);
                                print_slow(cout,"\nWhere are you going to go at this point?\nWhat is left?\nYou look around and there is no surrounding\nIt's all pitch white\nFor what you know the bottom can be endless\nEverything is quite there aren't even waves\nThe only sounds are created from you in here\nThere really isn't much to do\n\n1)Swim          2)Scream for help\n\n",60);
                                cin>>az;
                                if(az==1){label7:
                                    print_slow(cout,"\nYou start heading in front of you\nYou swim for about 10 minutes, until you feel tired,\nThen you stop and look around\nNo land, nothing at all, still white\n\n1)Swim again          2)Scream for help\n\n",60);
                                    cin>>ay;
                                    if(ay==1){
                                        goto label7;
                                    }
                                    else(ay==2);{
                                        goto label8;
                                    }
                                }
                                else(az==2);{label8:
                                print_slow(cout,"\nYou feel so lost that you start screaming in the hopeless attempt\nthat someone will come rescue you in that eternal void\n",60);
                                SetConsoleTextAttribute(hc, 0xF8);
                                SetFontSize(22);
                                print_slow(cout,"\n-HEYYY\n",40);
                                Sleep(500);
                                SetConsoleTextAttribute(hc, 0xF0);
                                print_slow(cout,"\nEverything starts feeling weird,\nLike you are getting out of your body\nSlowly becoming someone else,\nLooking at yourself from outside,\nYou keep screaming\n",60);
                                Sleep(500);
                                SetConsoleTextAttribute(hc, 0xF8);
                                SetFontSize(18);
                                print_slow(cout,"\n-IS THERE SOMEONE?\n",38);
                                Sleep(1300);
                                SetConsoleTextAttribute(hc, 0xF0);
                                print_slow(cout,"\nIt's all useless and you know it too\nBut yet, you keep going.\n",60);
                                Sleep(500);
                                SetConsoleTextAttribute(hc, 0xF8);
                                SetFontSize(15);
                                print_slow(cout,"\n-HELLO?\n",30);
                                Sleep(2000);
                                SetFontSize(12);
                                print_slow(cout,"\n-SOMEONE PLEASE\n",25);
                                Sleep(2500);
                                print_slow(cout,"\n-PLEASE SOMEONE HELP ME\n",20);
                                SetFontSize(8);
                                Sleep(3000);
                                SetConsoleTextAttribute(hc, 0xF0);
                                print_slow(cout,"\nBut nobody ever came...\n",60);
                                Sleep(500);
                                system("cls");
                                Sleep(300);
                                cambiaColoreSfondo(0,15);
                                SetConsoleTextAttribute(hc, 0x0F);
                                Sleep(200);
                                SetFontSize(24);
                                for (int i = 0; i <= total; ++i) {
                                displayProgressBar(i, total);
                                std::this_thread::sleep_for(std::chrono::milliseconds(50));}
                                Sleep(200);
                                goto label2;
                                }
                            }
                            else(aj==2);{//Scelta numero: 1.1.2.2.2.2.1.2
                                print_slow(cout,"\nYou stop right there\n",70);
                                Sleep(2000);
                                print_slow(cout,"You feel weak\nYou don't even feel your legs anymore\nYou try to catch your breath but it hardly seems you can't\nYou're sweating like never before, You loosen your tie\nYou look at the clear sky for a moment, at that point you feel your knee caps snapping and an unbearable amount of pain\nYou immediately fall on the ground and start screaming\nLooking at your leg you almost feel like trowing up\nThey are all bent and bloody",60);
                                //dafinire
                            }
                        }
                        else(w==2);{//Scelta numero: 1.1.2.2.2.2.2
                            print_slow(cout,"\nYou need to catch your breath, you stop and sit on the street",60);//da finire
                        }
                    }
                }
            }
        }
    }
    else(xxx==2);{//Scelta numero: 1.2
        print_slow(cout,"\nYou're tired to go every day in the same place,\nYou need something different today\nYour city is big and you want to have some fun\nSo you start walking to your car parked down the block\nWhere were you go?\n\n1)Go visit an old friend            2)Just drive around\n\n",55);
        cin>>d;
        if(d==1){//Scelta numero: 1.2.1
            print_slow(cout,"\nYou remember Josh an old friend of yours\n",60);
            SetConsoleTextAttribute(hc, 0x78);
            print_slow(cout,"'I should totally go check him out'",60);
            SetConsoleTextAttribute(hc, 0x70);
            print_slow(cout," you think\nYou calmly drive to his house\nA mid-range, average house in a not too good neighborhood near the forrest\nYou park in front of it, flick the cigarette out of the window and walk to his porch\nYou ring the bell",60);
            Sleep(1750);
            print_slow(cout,"\nNo one answers\n\n1)Go somewhere else.            2)Peek the window.\n\n",60);
            cin>>e;
            if(e==1){//Scelta numero: 1.2.1.1
                print_slow(cout,"\n\nYou don' wanna be too invasive,\nMaybe he's asleep or not in the house\nAnd also, you don't wanna go from an house to another\n",60);
                goto label3;
            }
            else(e==2);{//Scelta numero: 1.2.1.2
                print_slow(cout,"\nYou silently approach the window\nJust to see the corpse of josh laying on the sofa face down\n",60);
                SetConsoleTextAttribute(hc, 0x78);
                print_slow(cout,"`That dooshbag must be sleeping` ",60);
                SetConsoleTextAttribute(hc, 0x70);
                print_slow(cout,"\nYou ring a couple more times and see him flinch a little on his throne\nFrom the outside you notice that the place is filthy\nMultiple beer cans and alcohol bottles cover the small living room table\n\n1)Go somewhere else.          2)'Welcome yourself'\n\n",60);
                cin>>h;
                if(h==1){//Scelta numero: 1.2.1.2.1
                    print_slow(cout,"\nWow looks like he's not doing great\n",60);
                    SetConsoleTextAttribute(hc, 0x78);
                    print_slow(cout,"\n-Better let him off alone\n",45);
                    SetConsoleTextAttribute(hc, 0x70);
                    Sleep(500);
                    print_slow(cout,"\nYou think, and also\n",60);
                    goto label3;
                }
                else(h==2);{//Scelta numero: 1.2.1.2.2
                    print_slow(cout,"\nYou decide to make room for yourself\nIt won't be hard\nYou approach the nearest plant and find a key in the pot\n",60);
                    SetConsoleTextAttribute(hc, 0x78);
                    print_slow(cout,"'that idiot never change'",40);
                    SetConsoleTextAttribute(hc, 0x70);
                    print_slow(cout," You think giggling\nOpen the door and see something unexpected\nThe living room where Josh is sleeping is way too silent\nJosh's house is built in a weird way,\nBasically the kitchen and the saloon are in the same big room, both near the entrance\nYou take a few steps inside and first thing you notice is the table, There are few Jack bottles and a note\n\n1)Explore the house             2)Read the note.\n\n",60);
                    cin>>eh;
                    if(eh==1){//Scelta numero: 1.2.1.2.2.1 La root giusta per aprire il basement
                        print_slow(cout,"\nYou look at Josh for a second, completely passed out\nYou calmly move around the house, you basically know it as your pockets at this point\nYou get out of the big room and walk towards the rooms\nEverything is still and filthy as usual at this point\nJosh's room is instead surprisingly clean, like it has been cleaned recently\nIn depth ",60);
                        Sleep(1000);
                        print_slow(cout,"mhh unusual\nYou make your way into the bathroom and ",60);
                        Sleep(1200);
                        print_slow(cout,"it just sucks\nIt stinks, The shower is clearly broken and about to fall apart\nThere are brown and rad stains on: sink, shower, floor, mirror and even walls\nYou don't think you need to spend much more time in there\nYou can't even take a piss cause the toilet is clogged with toilet paper\nThis probably happened because josh is famous to throw parties pretty often at his house\nMaking it look like absolute shit afterwards\nAnd the house is pretty much done\nThere is the small back garden\nNothing special there just a few chairs with beer cans on and some uncutted grass\n",60);
                        Sleep(2000);
                        SetConsoleTextAttribute(hc, 0x78);
                        print_slow(cout,"\n-Oh shit there is also a basement\n",45);
                        Sleep(500);
                        SetConsoleTextAttribute(hc, 0x70);
                        print_slow(cout,"\nYou gently open the back door and go out in the garden\nYou use the chance to breath in some fresh air\nBut also in there weird stinks are able to reach you\nYou walk up to the tool house and just on the side of it there is the outer basement door\nYou open it wide\n",60);
                        Sleep(2500);
                        print_slow(cout,"\nAfter that you go down a few steps and reach the inner door\n",60);
                        Sleep(2500);
                        print_slow(cout,"\nExcept there is no door\nIt has been walled\n",60);
                        Sleep(1000);
                        SetConsoleTextAttribute(hc, 0x78);
                        print_slow(cout,"\n-Weird",40);
                        Sleep(400);
                        SetConsoleTextAttribute(hc, 0x70);
                        print_slow(cout,"\nInspecting it closer you notice a small hole innit\nAt first you try looking trough it but realize it's useless since you see nothing the other way\nOn a second inspection you notice that is more familiar than what you thought\nIt's a USB port\nWell nothing you can do about it\nSo you climb back up and re-enter the house\n\n1)Read the note.            2)Wake up Josh.\n\n",60);
                        cin>>aw;
                        if(aw==1){//Scelta numero: 1.2.1.2.2.1.1
                            print_slow(cout,"\nYou stealthily take the note and start reading\n\n",60);
                            system("start https://drive.google.com/file/d/1aTSZNnLV8ATaMhYtNAZFofOvp5CdN3R_/view?usp=drive_link");
                            Sleep(22000);
                            SetConsoleTextAttribute(hc, 0x78);
                            print_slow(cout,"\n-Fuck that's bad, poor josh\n",40);
                            Sleep(750);
                            SetConsoleTextAttribute(hc, 0x70);
                            print_slow(cout,"\nYou think it's the right time to wake him up\n",60);
                            goto label5;
                        }
                        else(aw==2);{//Scelta numero: 1.2.1.2.2.1.2
                            print_slow(cout,"\nYou look at Josh, poor guy going trough all that\nYou should cheer him a little up since you're here\nYou shout:\n",60);
                            SetConsoleTextAttribute(hc, 0x78);
                            print_slow(cout,"\n-Knock knock brother\n",50);
                            Sleep(500);
                            SetConsoleTextAttribute(hc, 0x70);
                            print_slow(cout,"\nHe moves a little trying to change position\nClearly not wake up\n",60);
                            SetConsoleTextAttribute(hc, 0x78);
                            print_slow(cout,"\n-ok then\n",40);
                            label5:
                            SetConsoleTextAttribute(hc, 0x70);
                            print_slow(cout,"\nYou walk up to him, his back is facing up\nYou slap his ass with your hand as hard as you can\nGrab and squish his whole cheek\n",60);
                            SetConsoleTextAttribute(hc, 0x78);
                            print_slow(cout,"\n-Good morning princess\n",40);
                            Sleep(500);
                            SetConsoleTextAttribute(hc, 0x70);
                            print_slow(cout,"\nHe immediately wakes up\nIt was too funny to not do it\n",60);
                            SetConsoleTextAttribute(hc, 0x79);
                            print_slow(cout,"\n-Jesus christ ",40);
                            cout<<nome;
                            print_slow(cout," what are you doing here?\n",35);
                            Sleep(500);
                            SetConsoleTextAttribute(hc, 0x78);
                            print_slow(cout,"\n-man i came to pay a visit, but now i feel like im saveing you from od\n",50);
                            SetConsoleTextAttribute(hc, 0x79);
                            Sleep(200);
                            print_slow(cout,"\n-nah man chill, im fine\n",65);
                            SetConsoleTextAttribute(hc, 0x70);
                            print_slow(cout,"\nHe says while he stretch his arms\n",60);
                            Sleep(500);
                            SetConsoleTextAttribute(hc, 0x78);
                            print_slow(cout,"\n-Listen ill'let you pull your shit togather then we'll talk\n-i'll clean\n",45);
                            Sleep(500);
                            SetConsoleTextAttribute(hc, 0x70);
                            print_slow(cout,"\nHe nods still zoned out\nThen heads twords the bathroom\nYou go to the kitchen and pick the black trash bags from a drawer\nYou start trowing various cans and bottles in the bag\nYou clean first the table, then the small desk, then the shelf\nWhile cleaning on there you see two envelopes\nYou know it isn't right to go trough someone else's stuff\nBut curiosity is eating you inside\nYou have to open at least one\n\n1)Envelope 1           2)Envelope 2\n\n",60);
                            cin>>at;
                            if(at==1){//Scelta numero: 1.2.1.2.2.1.2.1
                                print_slow(cout,"\nYou look at the envelope on the left\nIt comes in a black envelope, unusual\nYou reach to open it and notice that someone already opend it\n",60);
                                Sleep(750);
                                system("start https://drive.google.com/file/d/1Fx5Yc-MMVODA0rNOUfjAdmmLlFRMMaMk/view?usp=drive_link");
                                Sleep(30000);
                                print_slow(cout,"\nWow ok",60);
                                Sleep(3000);
                                print_slow(cout,"\nWho can be this by?\nAnd what the fuck did Josh put himself through\nWhile you wonder those questions you sit on the couch\n",60);
                                Sleep(2400);
                                goto label1;
                            }
                            else(at==2);{//Scelta numero: 1.2.1.2.2.1.2.2 IL FINALE IN CUI MC RIESCE AD APRIRE LA
                                Sleep(100);
                                print_slow(cout,"\n\nYou look at the envelope on the right\nIt's white and clean with a weird knob\nYou carefully pull the glue away with your keys\nOnce opened you take the paper out and start reading\n",60);
                                system("start https://drive.google.com/file/d/1mz-0L6530hZ1Yf8nisLeDxrAQOs7VVEa/view?usp=drive_link");
                                Sleep(16500);
                                print_slow(cout,"\nYou also notice a flash drive in it\nYou instantly connect the dots\nThis must be for the basement\nYou rush into the back garden and open the basement door quickly\nYou jump the few steps and land in front of the brick door\n",60);
                                Sleep(400);
                                print_slow(cout,"\nAnd after a few attempts you successfully insert the USB",60);//dafinire

                            }
                        }
                        }
                        
                    else(eh==2);{//Scelta numero: 1.2.1.2.2.2 
                        print_slow(cout,"\nYou stealthily take the note and start reading\n\n",60);
                        system("start https://drive.google.com/file/d/1aTSZNnLV8ATaMhYtNAZFofOvp5CdN3R_/view?usp=drive_link");
                        Sleep(22000);
                        print_slow(cout,"That's fucked up\nYou wasn't expecting that at all\nYou put back the letter and think for a bit\n\n1)Wake up Josh            2)Explore the House\n\n",60);
                        cin>>j;
                        if(j==1){//Scelta numero: 1.2.1.2.2.2.1
                            print_slow(cout,"\nYou look at Josh, poor guy going trough all that\nYou should cheer him a little up since you're here\nYou shout:\n",60);
                            SetConsoleTextAttribute(hc, 0x78);
                            print_slow(cout,"\n-Knock knock brother\n",50);
                            Sleep(500);
                            SetConsoleTextAttribute(hc, 0x70);
                            print_slow(cout,"\nHe moves a little trying to change position\nClearly not wake up\n",60);
                            SetConsoleTextAttribute(hc, 0x78);
                            print_slow(cout,"\n-ok then\n",40);
                            SetConsoleTextAttribute(hc, 0x70);
                            print_slow(cout,"\nYou walk up to him, his back is facing up\nYou slap his ass with your hand as hard as you can\nGrab and squish his whole cheek\n",60);
                            SetConsoleTextAttribute(hc, 0x78);
                            print_slow(cout,"\n-Good morning princess\n",40);
                            Sleep(500);
                            SetConsoleTextAttribute(hc, 0x70);
                            print_slow(cout,"\nHe immediately wakes up\nIt was too funny to not do it\n",60);
                            SetConsoleTextAttribute(hc, 0x79);
                            print_slow(cout,"\n-Jesus christ ",40);
                            cout<<nome;
                            print_slow(cout," what are you doing here?\n",35);
                            Sleep(500);
                            SetConsoleTextAttribute(hc, 0x78);
                            print_slow(cout,"\n-man i came to pay a visit, but now i feel like im saveing you from od\n",50);
                            SetConsoleTextAttribute(hc, 0x79);
                            Sleep(200);
                            print_slow(cout,"\n-nah man chill, im fine\n",65);
                            SetConsoleTextAttribute(hc, 0x70);
                            print_slow(cout,"\nHe says while he stretch his arms\n",60);
                            Sleep(500);
                            SetConsoleTextAttribute(hc, 0x78);
                            print_slow(cout,"\n-Listen ill'let you pull your shit togather then we'll talk\n-i'll clean\n",45);
                            Sleep(500);
                            SetConsoleTextAttribute(hc, 0x70);
                            print_slow(cout,"\nHe nods still zoned out\nThen heads twords the bathroom\nYou go to the kitchen and pick the black trash bags from a drawer\nYou start trowing various cans and bottles in the bag\nYou clean first the table, then the small desk, then the shelf\nWhile cleaning on there you see two envelopes\nYou know it isn't right to go trough someone else's stuff\nBut curiosity is eating you inside\nYou have to open at least one\n\n1)Envelope 1           2)Envelope 2\n\n",60);
                            cin>>ao;
                            if(ao==1){//Scelta numero: 1.2.1.2.2.2.1.1
                                print_slow(cout,"\nYou look at the envelope on the left\nIt comes in a black envelope, unusual\nYou reach to open it and notice that someone already opend it\n",60);
                                Sleep(1000);
                                system("start https://drive.google.com/file/d/1Fx5Yc-MMVODA0rNOUfjAdmmLlFRMMaMk/view?usp=drive_link");
                                Sleep(30000);
                                print_slow(cout,"\nWow ok",60);
                                Sleep(3000);
                                print_slow(cout,"\nWho can be this by?\nAnd what the fuck did Josh put himself through\nWhile you wonder those questions you sit on the couch\n",60);
                                Sleep(2400);
                                goto label1;
                            }
                            else(ao==2);{//Scelta numero: 1.2.1.2.2.2.1.2
                                Sleep(100);
                                print_slow(cout,"\n\nYou look at the envelope on the right\nIt's white and clean with a weird knob\nYou carefully pull the glue away with your keys\nOnce opened you take the paper out and start reading\n",60);
                                system("start https://drive.google.com/file/d/1mz-0L6530hZ1Yf8nisLeDxrAQOs7VVEa/view?usp=drive_link");
                                Sleep(30000);
                                print_slow(cout,"\nYou also notice a flash drive in it\nInspecting it it looks like a normal USB\nYou don't know what to do with it so you just put everything back\n",60);
                                Sleep(1500);
                                print_slow(cout,"\nSo you sit on the couch waiting for Josh to get ready\nYou scroll trough your phone meanwhile\n",60);
                                Sleep(2000);
                                system("start https://drive.google.com/file/d/1hSbz8di-He8dNCGFT75vnCkeg-iiXnHL/view?usp=drive_link");
                                Sleep(3500);
                                print_slow(cout,"\nMemes funny",60);
                                int ctd;
                                delete_slow(std::cout, ctd, 60);
                                Sleep(500);
                                label1:
                                print_slow(cout,"\nNot even the time to do some really important things on\nyour phone, like telling your boss you won't make it to work.\n",60);
                                Sleep(1500);
                                print_slow(cout,"\nThat you notice Josh standing in front of you\n",60);
                                SetConsoleTextAttribute(hc, 0x79);
                                Sleep(400);
                                print_slow(cout,"\n-Hey pal ",40);
                                Sleep(300);
                                print_slow(cout,"so what are we doing?\n",45);
                                Sleep(200);
                                SetConsoleTextAttribute(hc, 0x78);
                                print_slow(cout,"\n-Uhm i mean we could",50);
                                Sleep(1600);
                                SetConsoleTextAttribute(hc, 0x70);
                                print_slow(cout,"\n\n1)",60);
                                SetConsoleTextAttribute(hc, 0x78);
                                print_slow(cout,"-Go to a club          ",60);
                                SetConsoleTextAttribute(hc, 0x70);
                                print_slow(cout,"2)",60);
                                SetConsoleTextAttribute(hc, 0x78);
                                print_slow(cout,"-Go on a boat trip\n\n",60);
                                SetConsoleTextAttribute(hc, 0x70);
                                cin>>bb;
                                if(bb==1){//Scelta numero: 1.2.1.2.2.X.X.X.1
                                    //finale felice in cui vai ad un festival con josh e si trova una piskella
                                }
                                else(bb==2);{//Scelta numero: 1.2.1.2.2.X.X.X.2
                                    print_slow(cout,"\nYou feel like a nice cruise would be good for the both of you\nYou're even willing to pay for it all\nIt's right to spend for your homies sometimes\n",60);
                                    Sleep(750);
                                    SetConsoleTextAttribute(hc, 0x78);
                                    print_slow(cout,"\n-Hey man wanna go on a free cruise\n",40);
                                    Sleep(250);
                                    SetConsoleTextAttribute(hc, 0x79);
                                    print_slow(cout,"\n-Hell yeah man who wouldn't want to!\n",60);
                                    Sleep(100);
                                    SetConsoleTextAttribute(hc, 0x78);
                                    print_slow(cout,"\n-Hell yeah man let's go\n",45);
                                    SetConsoleTextAttribute(hc, 0x70);
                                    PlaySound(TEXT("./music/EXP.wav"), NULL, SND_ASYNC );
                                    //daaggiungfere canzone
                                    print_slow(cout,"\nAfter that you hear a loud bang\nIt's so loud it it makes your ears whistle\nThe walls in Josh's house shake, almost like an earthquake\nJosh panics\n",60);
                                    SetConsoleTextAttribute(hc, 0x79);
                                    print_slow(cout,"\n-Holy shit fuck fuck fuck\n",30);
                                    SetConsoleTextAttribute(hc, 0x70);
                                    print_slow(cout,"\nHe starts running somewhere\nYou tag along\nHe goes straight to the backyard, just to see a brutal scene in front of you\nThe explosion came from something in Josh's basement\n",60);
                                    Sleep(750);
                                    SetConsoleTextAttribute(hc, 0x79);
                                    print_slow(cout,"\n-Shit man what am i supposed to do now\n-SHITT\n",30);
                                    SetConsoleTextAttribute(hc, 0x70);
                                    print_slow(cout,"\nYou look at him confused for a second\n",60);
                                    SetConsoleTextAttribute(hc, 0x78);
                                    print_slow(cout,"\n-I would start by calling the fire department to be honest\n",35);
                                    SetConsoleTextAttribute(hc, 0x79);
                                    print_slow(cout,"\n-Right, right shit\n",40);
                                    SetConsoleTextAttribute(hc, 0x70);
                                    print_slow(cout,"\n while Josh calls the water guys you walk a little closer to the explosion sight\nEven if it's smoking, on fire and dangerous\n",60);
                                    Sleep(750);
                                    print_slow(cout,"\nIt looks like it came from underground\nProbably from the basement\nIt might have been a tube or a gas tank\nOr at least you hope because the other option is josh making bombs\n",60);
                                }
                            }
                        }
                        else(j==2);{//Scelta numero: 1.2.1.2.2.2.2
                            SetConsoleTextAttribute(hc, 0x70);
                            print_slow(cout,"\nYou look at Josh for a second, completely passed out\nYou calmly move around the house, you basically know it as your pockets at this point\nYou get out of the big room and walk towards the rooms\nEverything is still and filthy as usual\nOn your way there tho you trip over some can's\nIn a goofy attempt to not fall you end up knocking over a picture of Josh and Beth\nIt falls on the ground shattering the glass cover and making a huge noise",60);
                            Sleep(1500);
                            print_slow(cout,"\nJosh wakes up\n",60);
                            Sleep(1500);
                            print_slow(cout,"\nHe rushes over to you sort of panicked\nHe laughs as soon as he realizes it's you\n",60);
                            Sleep(300);
                            SetConsoleTextAttribute(hc, 0x79);
                            print_slow(cout,"\n-HAHAHAHAHA ",20);
                            cout<<nome;
                            print_slow(cout," it's you!\n",30);
                            Sleep(500);
                            print_slow(cout,"-Come sit let's have a talk\n",50);
                            Sleep(750);
                            SetConsoleTextAttribute(hc, 0x70);
                            print_slow(cout,"\nYou both walk trough the mess onto the couch\n",60);
                            Sleep(3000);
                            print_slow(cout,"He sits back on there you sit on the smaller leather chair\n",60);
                            Sleep(750);
                            SetConsoleTextAttribute(hc, 0x79);
                            print_slow(cout,"\n-Man sorry for the mess,\n-I've been throwing a lot of partyes since me and Beth broke up\n",45);
                            Sleep(200);
                            SetConsoleTextAttribute(hc, 0x78);
                            print_slow(cout,"\n-No need to apologize man",40);
                            Sleep(300);
                            print_slow(cout,"\n-To be honest i would have come if i didn't had to wake up early\n",36);
                            SetConsoleTextAttribute(hc, 0x70);
                            print_slow(cout,"\nLiar, you play videogames till 5 am, you just didn't want to\n",60);
                            SetConsoleTextAttribute(hc, 0x78);
                            print_slow(cout,"\n-You still feel bad for that bitch?\n",45);
                            Sleep(500);
                            SetConsoleTextAttribute(hc, 0x79);
                            print_slow(cout,"\n-Nah man you know me, 3 days and im back on track\n",45);
                            Sleep(500);
                            print_slow(cout,"-Iamma take a shower real quick and then we can do something alright?\n",45);
                            SetConsoleTextAttribute(hc, 0x78);
                            print_slow(cout,"\n-Alright",40);
                            SetConsoleTextAttribute(hc, 0x70);
                            Sleep(750);
                            print_slow(cout,"\nHe stands up and go you take out your phone and wait\n",60);
                            Sleep(4500);
                            goto label1;
                        }
                    }
                
                 }
            }
        }
        else(d==2);{//Scelta numero: 1.2.2
            label3:
            SetConsoleTextAttribute(hc, 0x78);
            print_slow(cout,"\n-Sometimes life is about exploring\n",40);
            Sleep(200);
            SetConsoleTextAttribute(hc, 0x70);
            print_slow(cout,"\nSo you enter you car and speed off\nDriving freely makes you feel good\nYou never know what life has to offer you\nYou think as the gray of the city starts turning into green of the nature\nAll of a sudden a surprise actually strikes you\nIt's a long line of traffic in the middle of nothing\n\n1)Wait for it to pass.             2)Get out the car.\n\n",60);
            cin>>f;
            if(f==1){//Scelta numero: 1.2.2.1
                print_slow(cout,"\nYou decide to take it easy as you should,\nYou roll down the windows and let some of that fresh air in.\n",60);
                Sleep(2000);
                print_slow(cout,"\nSince there is traffic you pull out your phone and text your boss you won't make it to work\nYou are not taking this job seriously at all,\nAt this rate they will probably fire you\n",60);
                Sleep(1000);
                SetConsoleTextAttribute(hc, 0x78);
                print_slow(cout,"\n-Jesus..\n",40);
                SetConsoleTextAttribute(hc, 0x70);
                print_slow(cout,"\nYou start going trough your cd's to hear your thoughts a little less\n",60);
                Sleep(500);
                SetConsoleTextAttribute(hc, 0x78);
                print_slow(cout,"\n-Oh this shit is a classic\n",40);
                SetConsoleTextAttribute(hc, 0x70);
                Sleep(500);
                print_slow(cout,"\nYou insert the disk and hit the shuffle button\n",60);
                PlaySound(TEXT("./music/SHSA.wav"), NULL, SND_FILENAME | SND_ASYNC );
                Sleep(1500);
                SetConsoleTextAttribute(hc, 0x78);
                print_slow(cout,"\n-Much better eh",45);
                Sleep(1000);
                print_slow(cout,"\n-Mind as well\n",50);
                SetConsoleTextAttribute(hc, 0x70);
                Sleep(750);
                print_slow(cout,"\nYou reach to the car drawer and open it\nInside other then the car insurance and a few papers there is something you care more about\nA lovely rolled joint\nIn the calm of the traffic you put it in your mouth and light it up\nIt's 11:34, you usually don't smoke this early\nThe time passes, the traffic slowly moves\n",60);
                Sleep(2000);
                print_slow(cout,"\nWhere are you even going?\n\n1)Go to the beach           2)Go to the airport\n\n",60);
                cin>>ar;
                if(ar==1){
                    //dafinire
                }
                else(ar==2);{
                    print_slow(cout,"\nAs you puff the joint the traffic starts to flow again\nYou finally can give a purpose to your Mitsubishi Lancer.\n",60);
                    Sleep(750);
                    SetConsoleTextAttribute(hc, 0x78);
                    print_slow(cout,"\n-I want to get out of this fucking city\n",40);
                    SetConsoleTextAttribute(hc, 0x70);
                    print_slow(cout,"\nYou press on the pedal sliding trough the six lane high way\nAnd with your arm out of the window the trip progresses smoothly\n",60);
                    //dafinire
                }
            }
            else(f==2);{//Scelta numero: 1.2.2.2
                SetConsoleTextAttribute(hc, 0x78);
                print_slow(cout,"\n-I have no time for this\n",45);
                Sleep(300);
                SetConsoleTextAttribute(hc, 0x70);
                print_slow(cout,"\nYou think as people on the road look at you stunned\nYou get out not caring about the car and start walking,\nThe road is built near a forest,\nthere is a path connecting it from the sidewalk\nYou look into the forrest,",60);
                Sleep(1000);
                print_slow(cout,"\nFeels like it stares back\nYou start walking innit,\nThe more you venture in the darkwood the more clacsons and overall noise of the city goes silent,\n\nYou ever barely visited this forest as a kid, your mom was always worried you could get lost\nYou get why now, This forest is huge,\nYou walk for about 15' in a straight line, But from the surroundings it almost look like you haven't moved at all\nIt's always tall dark trees on a soft humid ground\n",60);
                Sleep(1000);
                print_slow(cout,"As you keep walking you stumble upon something weird none the less\nOn your right here is a set of stairs coming out the ground, seemingly leading to nothing,\nIll'attach a picture i took to make you better understand\n",45);
                system("start https://drive.google.com/file/d/1drm0LofUJu2tNm6W-YYlXVTS9cOgN3eY/view?usp=drive_link");//dacambiare
                Sleep(8000);
                print_slow(cout,"\nThat look so out of place, You curiously walk up to them\nStepping on them you start feeling them\nJust plain metal stairs, Why would you build in a forest something that looks straight out a office\n\n1)See where they lead          2)Run away\n\n",60);
                cin>>s;
                if(s==1){//Scelta numero: 1.2.2.2.1
                    print_slow(cout,"\nYou look down the stairs expecting them just to be covered in dirt\nWhat you actually see it's just\n",60);
                    Sleep(400);
                    print_slow(cout,"\nStairs",60);
                    Sleep(300);
                    print_slow(cout,"\nAs far as the eye can stretch\n\nStairs.\n",60);
                    Sleep(400);
                    print_slow(cout,"\nYou start walking down them slowly\nWith every step they produce a loud metallic sound,\nYou go on for a few minutes.\nIt gets darker, colder like in a basement, a little humid\nThe more you go the rustier the stairs become.\n",60);
                    Sleep(700);
                    print_slow(cout,"\nThe air becomes heavier\nIt's hard for oxygen to come this far down\nYou are about 50 steps down and it still seems like a long way\n\nYour head starts hurting\n\n1)Keep going          2)Go back up\n\n",60);
                    cin>>k;
                    if(k==1){//Scelta numero: 1.2.2.2.1.1
                        SetConsoleTextAttribute(hc, 0x78);
                        print_slow(cout,"\n-Stupid fucking stairs\n",40);
                        SetConsoleTextAttribute(hc, 0x70);
                        Sleep(500);
                        print_slow(cout,"\nIt became a challenge between yourself\nYou start descend faster\nIt gets darker every step\nAt about 200 steps is completely dark.",60);
                        Sleep(2000);
                        system("cls");
                        cambiaColoreSfondo(0,0);
                        SetConsoleTextAttribute(hc, 0x0F);
                        PlaySound(TEXT("./music/BL.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
                        Sleep(500);
                        print_slow(cout,"\nAbout 50 steps later you accidentally trip and fall\nYou placed your foot on the ground to take another step, but found none\nYou arrived at the end\nNo more stairs\n\n",60);
                        Sleep(1000);
                        print_slow(cout,"\nIt's still too dark to see tho\n...",60);
                        Sleep(1200);
                        SetConsoleTextAttribute(hc, 0x0C);
                        cout<<"\n                                               .\n";
                        Sleep(1000);
                        SetConsoleTextAttribute(hc, 0x0F);
                        print_slow(cout,"\n\nYou notice a small red light in the distance.\nWith no other option you walk up to it\nIt's some kind of machine\n...",60);
                        Sleep(1000);
                        SetConsoleTextAttribute(hc, 0x08);
                        print_slow(cout,"\n-Oh shit it's a generator.",45);
                        Sleep(700);
                        print_slow(cout,"\n-A generator underground?\n",55);
                        SetConsoleTextAttribute(hc, 0x0F);
                        Sleep(600);
                        print_slow(cout,"\nYou push the questions away for a second and start looking for a way to fire it up\nAnd right there, under the red light there is a button\n",60);
                        Sleep(500);
                        print_slow(cout,"\nYou press it.",60);
                        Sleep(2000);
                        system("cls");
                        cambiaColoreSfondo(7,0);
                        SetConsoleTextAttribute(hc, 0x78);
                        Sleep(750);
                        print_slow(cout,"\n-Wow this rust box actually worked\n",55);
                        Sleep(500);
                        SetConsoleTextAttribute(hc, 0x70);
                        print_slow(cout,"\nThe light was back and the generator didn't explode, so that's something\nYou seize the opportunity to have a look around\n",60);
                        Sleep(1000);
                        print_slow(cout,"\nThe first thing you notice is that the room you're in is pretty big,\nBigger then your living room for sure\nThe walls looks made out of steel sheets\nJust like the stairs.\n\n",60);
                        Sleep(1000);
                        print_slow(cout,"\nOther then the generator the room is pretty much empty\nOnly some pipes on the ceiling\nCurious you start follow where they lead\n",60);
                        Sleep(1500);
                        print_slow(cout,"The pipes extend trough a corridor,\nA very long corridor\nIt took you almost ten minutes to walk trough it all\nNothing out of the ordinary here, just an underground tunnel\nA lot of cities have them\nYou eventually arrive at the end\nThe pipe splits in two\nThey both go into walls, into rooms\nBoth on your left and right\nOne has a little window that emits a subtle green light\nThe other one has no window but from under it you see a purple glow\n\n",60);
                        Sleep(1000);
                        SetConsoleTextAttribute(hc, 0x72);
                        print_slow(cout,"1)Door on your left.            ",60);
                        SetConsoleTextAttribute(hc, 0x75);
                        print_slow(cout,"2)Door on your right.\n\n",60);
                        SetConsoleTextAttribute(hc, 0x70);
                        cin>>ap;
                        if(ap==1){//Scelta numero: 1.2.2.2.1.1.1
                            PlaySound(TEXT("./music/Rebirth.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
                            SetConsoleTextAttribute(hc, 0x70);
                            print_slow(cout,"\nYou're curious about the door on the left\nThat green light seems so strong, you wonder what could emit it.\n",60);
                            Sleep(200);
                            print_slow(cout,"\nYou walk towards it\n",60);
                            Sleep(750);
                            print_slow(cout,"\nYou try to look inside trough the window but that light is so strong it almost blinds you\nYou push the handle, it's not a normal one\nIt's like an anti-panic handle\nThe door immediately opens letting all the light out and just you in,\n",60);
                            Sleep(1000);
                            print_slow(cout,"\nComing in you feel something crack under your foot\nYou stepped on a pair of sunglasses\nYou did not break them\n",60);
                            Sleep(200);
                            SetConsoleTextAttribute(hc, 0x78);
                            print_slow(cout,"\n-Too perfect to be true huh\n",45);
                            SetConsoleTextAttribute(hc, 0x70);
                            print_slow(cout,"\nYou put the sunglasses on to avoid the strong light\n",60);
                            Sleep(500);
                            print_slow(cout,"\nBeing able to see inside you notice a person in the middle of the room\nIt look's like a woman from the hair and the brest\nShe's dressed like a corpo employ all black\nA headset covers half of her face is also the source of the light\nShe's sitting on what looks like an old dentist chair\n",60);
                            Sleep(500);
                            print_slow(cout,"\nWalking around the room you notice is pretty empty other for the girl\nOn the opposite side of the door, on the wall there is a cork board\nIt looks really complex and full, there are a lof of small drawings, even on the wall around\nYou can't understand it\nThe headset she's wearing has cables that are connected to the pipe you were following\nThere is a table beside her with a phone\n\nNow that you think about it even her wearing a headset since that technology should still be in his early stages\n",60);
                            Sleep(750);
                            print_slow(cout,"\nThe woman is still, looks asleep almost\nYou get curious and want to take a peek into the headset\nYou are even willing to argue with the woman after\nYou silently walk up to the side of the chair\n",60);
                            Sleep(500);
                            print_slow(cout,"\nTrying to take the headset off you feel it stuck to her\nYou don't wanna force it and maybe cause damage\nYou walk behind her and notice another cable coming out of her nape\n",60);
                            Sleep(1000);
                            SetConsoleTextAttribute(hc, 0x78);
                            print_slow(cout,"\n-That's weird\n",40);
                            SetConsoleTextAttribute(hc, 0x70);
                            Sleep(750);
                            print_slow(cout,"\nDid she made it herself?\nCould she be a netrunner or something like that\nMaybe you'll ask her when she wakes up\n",60);
                            Sleep(750);
                            print_slow(cout,"\nAnyway you reach for the cable and hope for the best\nYou take a deep breath and unplug it.",60);
                            Sleep(1500);
                            PlaySound(NULL, 0, 0);
                            MessageBox(NULL,"This program encountered a fatal error!","You were disconnected",MB_ICONERROR | MB_OK);
                            break;
                        }
                        else(ap==2);{//Scelta numero: 1.2.2.2.1.1.2
                            PlaySound(TEXT("./music/LV.wav"), NULL, SND_FILENAME | SND_ASYNC );
                            SetConsoleTextAttribute(hc, 0x70);
                            print_slow(cout,"\nYou look at both doors for a second,\nApproaching the right one you hear sobbing coming from the other side\nIs someone there?\n",60);
                            Sleep(1000);
                            print_slow(cout,"\nYou gently push the door and open it\n\nInside you notice right off that there actually is someone crying\nThe room just looks like a really advanced guest room\nIt has a big shower from the opposite side of the door,\nOn the left of the room there is the bed where that person is laying,\nShe looks like a woman from the long black hair\nShe didn't hear you come in yet\nOn the right side instead there is a table with various stuff\nFirstly you notice what seems like computer parts and near it a server rack\nThey're not in good conditions,\nLike someone build and tared something apart multiple times\n",60);
                            Sleep(1500);
                            print_slow(cout,"\nGetting closer your attention goes onto a cork board on the wall over the table\nThere are some sticky notes on it with names and serial numbers on theme\nThere is also a weird drawing\n",60);
                            Sleep(1500);
                            system("start https://drive.google.com/file/d/1pXTzl8ev3qYX9wIKc10mpMAR5qqwJUCM/view?usp=drive_link");
                            Sleep(12000);
                            SetConsoleTextAttribute(hc, 0x78);
                            print_slow(cout,"\n-Four walls, one eye\n",45);
                            Sleep(1500);
                            SetConsoleTextAttribute(hc, 0x70);
                            print_slow(cout,"\nWhile you're analyzing the picture to get something out of it\n",60);
                            Sleep(500);
                            SetConsoleTextAttribute(hc, 0x75);
                            print_slow(cout,"\n-AAAAHH WHAT THE FUCK\n",32);
                            Sleep(400);
                            SetConsoleTextAttribute(hc, 0x70);
                            print_slow(cout,"\nShe spotted you\nYou stay silent, giving her your back\n",60);
                            Sleep(800);
                            SetConsoleTextAttribute(hc, 0x75);
                            print_slow(cout,"\n-Wait ",40);
                            cout<<nome;
                            print_slow(cout," is that you?\n",45);
                            Sleep(1000);
                            SetConsoleTextAttribute(hc, 0x70);
                            print_slow(cout,"\nYou freeze up for a second\nWhy does she know's your name?\nDo you know each other?\n",60);
                            Sleep(1500);
                            print_slow(cout,"\nYou turn around\n",60);
                            Sleep(1000);
                            SetConsoleTextAttribute(hc, 0x75);
                            print_slow(cout,"\n-Dude what the fuck are you doing here, answer me\n",38);
                            Sleep(1000);
                            SetConsoleTextAttribute(hc, 0x70);
                            print_slow(cout,"\nIn front of you there is a fairly short girl with black hair and eyes\nHeavy make up and a really punk dressing style\nYou've never seen her before\n",60);
                            Sleep(400);
                            SetConsoleTextAttribute(hc, 0x78);
                            print_slow(cout,"\n-I've just stumbled upon here, but who the fuck are you supposed to be?\n",60);
                            SetConsoleTextAttribute(hc, 0x70);
                            print_slow(cout,"\nYou two look into each other's eyes in silence for a second",60);
                            Sleep(2000);
                            print_slow(cout,"\nThen she screams\n",60);
                            SetConsoleTextAttribute(hc, 0x75);
                            print_slow(cout,"\n-Jesus fucking christ ",30);
                            cout<<nome;
                            print_slow(cout," we work in the same fucking office",30);
                            Sleep(1200);
                            print_slow(cout,"\n-Not only that but i always fucking...\n",35);
                            Sleep(500);
                            SetConsoleTextAttribute(hc, 0x70);
                            print_slow(cout,"\nShe stops and snorts\n",60);
                            Sleep(1000);
                            SetConsoleTextAttribute(hc, 0x78);
                            print_slow(cout,"\n-Listen im sorry if i interrupted, i've just came across this pl-\n",40);
                            SetConsoleTextAttribute(hc, 0x70);
                            print_slow(cout,"\nNot even the time to finish that she interrupts you abruptly\n",60);
                            SetConsoleTextAttribute(hc, 0x75);
                            print_slow(cout,"\n-Did you see her in the other room?\n",65);
                            Sleep(500);
                            SetConsoleTextAttribute(hc, 0x78);
                            print_slow(cout,"\n-No?\n",80);
                            Sleep(1000);
                            SetConsoleTextAttribute(hc, 0x70);
                            print_slow(cout,"\nFrom the serious expression that she had, now she forms a big smile\nOn the verge of laughing\n",60);
                            Sleep(750);
                            SetConsoleTextAttribute(hc, 0x75);
                            print_slow(cout,"\n-Ok alright\n",40);
                            SetConsoleTextAttribute(hc, 0x70);
                            print_slow(cout,"\nShe stands up\n",60);
                            SetConsoleTextAttribute(hc, 0x75);
                            print_slow(cout,"\n-Perfect actually ehehahe\n",35);
                            Sleep(100);
                            SetConsoleTextAttribute(hc, 0x78);
                            print_slow(cout,"\n-Why, what's in the other room?\n",50);
                            Sleep(100);
                            SetConsoleTextAttribute(hc, 0x70);
                            print_slow(cout,"\nHer laugh gets just a little more intense\nThen she breaks it with a cough\nDuring all this dialogue since she got up she's been messing with objects around the room\n",60);
                            SetConsoleTextAttribute(hc, 0x75);
                            print_slow(cout,"\n-Ooh nothing indeed...\n",30);
                            Sleep(200);
                            print_slow(cout,"-Maybe we will make sure you never see that?\n",30);
                            SetConsoleTextAttribute(hc, 0x70);
                            print_slow(cout,"\nShe gets close\n",50);
                            SetConsoleTextAttribute(hc, 0x78);
                            print_slow(cout,"\n-What? wh-\n",70);
                            system("cls");
                            cambiaColoreSfondo(0,0);
                            PlaySound(TEXT("./music/scream.wav"), NULL, SND_FILENAME | SND_ASYNC);
                            PlaySound(TEXT("./music/SPOP.wav"), NULL, SND_FILENAME | SND_ASYNC |SND_NOTOP );
                            Sleep(6000);
                            SetConsoleTextAttribute(hc, 0x0F);
                            print_slow(cout,"\n.in the middle of your sentence she splashes you with a small glass of liquid all over your face.\n.in the first instant you feel a pinching cold.\n.way too cold.\n.cold enough to burn you.\n.you don't know what that is but you can't do nothing but scream on top of your lungs.\n.you also fall on the table behind you hurting yourself even more.\n.that liquid quickly penetrate into your eyes.\n\n.making you blind.\n\n.with he little force you have you scream at her.\n",60);
                            Sleep(500);
                            SetConsoleTextAttribute(hc, 0x08);
                            print_slow(cout,"\n-WHY, WHY DID YOU DO IT",25);
                            Sleep(750);
                            print_slow(cout,"\n-FUCK IT HURT SO MUCH\n-WE COULD HAVE TALKED\n-FUCK FUCK FUCK\n",25);
                            Sleep(750);
                            SetConsoleTextAttribute(hc, 0x05);
                            print_slow(cout,"\n-Oh you're so naive, you know how you can find me don't you\n",38);
                            SetConsoleTextAttribute(hc, 0x0F);
                            print_slow(cout,"\n.her voice is calm for a second.\n.you feel her moving towards you.\n",60);
                            SetConsoleTextAttribute(hc, 0x05);
                            print_slow(cout,"\n-I don't care where you will arrive\n-I only care that-\n",30);
                            SetConsoleTextAttribute(hc, 0x0F);
                            print_slow(cout,"\n.you hear her starting to sob again.\n.now she's on top of you.\n",60);
                            SetConsoleTextAttribute(hc, 0x05);
                            print_slow(cout,"\n-I ONLY CARE I CAN'T TAKE YOUR PLACE YOU FUCKING IDIOT\n",35);
                            SetConsoleTextAttribute(hc, 0x0F);
                            print_slow(cout,"\n.you feel her cold hands grabbing your neck.\n.she's tightening the grip and pushing her nails in your skin.\n.you hear her sobbing meanwhile.\n.you try to resist at first but you're short out of energy and also still in pain.\n",60);
                            Sleep(4000);
                            print_slow(cout,"\n.and also short out of breath\n",60);
                            Sleep(2000);
                            print_slow(cout,"\n.and in what feels almost like falling asleep\n",60);
                            Sleep (1750);
                            system("cls");
                            cambiaColoreSfondo(0,15);
                            Sleep(500);
                            for (int i = 0; i <= total; ++i) {
                            displayProgressBar(i, total);
                            std::this_thread::sleep_for(std::chrono::milliseconds(50));}
                            goto label2;
                        }
                    }
                    else(k==2);{//Scelta numero: 1.2.2.2.1.2

                    }
                }
                else(s==2);{//Scelta numero: 1.2.2.2.2
                    print_slow(cout,"\nThese stairs makes you tense,\nYou start backing from them while still keeping an eye on them\n",60);
                    Sleep(1000);
                    PlaySound(TEXT("./music/WH.wav"), NULL, SND_FILENAME | SND_ASYNC);
                    PlaySound(TEXT("./music/Deadlyness.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NSTOP );
                    print_slow(cout,"\nYou notice the further away you go the more you start hearing whispers in the distance\nYou turn around and walk in the direction you came from",60);
                    Sleep(1000);
                    print_slow(cout,"\nBut when you turn around\n",60);
                    Sleep(1000);
                    print_slow(cout,"You just see another set of stairs in front of you",60);
                    Sleep(1000);
                    //dafinire finale in cui finisici su una spiaggia in stile death stranding
                }
            }
        }
    }
    }
    else(ac==2);{//Scelta numero: 2
    cout<<"\nYou don't really feeling like doing much today\nYou feel bored already\nAnd thinking about facing the day demotivates you\nYou don't enjoy doing the same thing over and over anymore\nYou think that's ok as soon as that stays between You and You, right?\n\n1)Yes.           2)Not Really.\n"<<endl;
    cin>>a;
    if(a==1){

    }
    else(a==2);{

    }
    }
    break;
    
    }
    case 2:{
    
    break;
    }
    }
    return 0;
}

