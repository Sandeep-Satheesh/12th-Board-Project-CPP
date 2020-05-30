#include<fstream.h>
#include<conio.h>
#include<iomanip.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<process.h>
#include<dos.h>
#include<ctype.h>
#include<time.h>

#define lsa 261.626
#define lri 277.183
#define hri 293.665
#define lga 311.127
#define hga 329.628
#define lma 349.228
#define hma 369.994
#define pa 391.995
#define lda 415.305
#define hda 440
#define lni 466.164
#define hni 493.883
#define hsa 523.251
#define plri 554.365
#define phri 587.660
#define plga 311
#define phga 329.628
#define plma 349.228
#define phma 369.994
#define ppa 391.995
#define plda 415.405
#define phda 440
#define phni 493.883
#define plni 466.164
#define phsa 523.251
#define nlsa 130.813
#define nlri 138.591
#define nhri 146.832
#define nlga 155.563
#define nhga 164.814
#define nlma 174.614
#define nhma 184.997
#define npa 195.998
#define nlda 207.652
#define nhda 220
#define nlni 233.832
#define nhni 246.942

char letters[53],sounds = 0, pwd[9], database[15] = "ATLASLST.DB"; enum MUSIC {SUCCESS, FAILURE, CRITERR, COMP, SURVIVA, TANKACE};

void decrypt(char[]), encrypt(char[]);
void play (char music) {
	if (!sounds) return;
	else if (music == SURVIVA) {

		sound(lsa); delay(250); nosound(); sound(hri); delay(250); nosound(); sound(lsa); delay(250); nosound(); sound(nlni); delay(250); nosound();
		for (int i = nhni; i <= lsa; i+=3) { sound(i); delay(40); nosound(); } sound(lsa); delay(150); nosound();

		sound(nlni); delay(100); nosound(); sound(npa); delay(500);

		sound(lsa); delay(250); nosound(); sound(hri); delay(250); nosound(); sound(lsa); delay(250); nosound(); sound(nlni); delay(250); nosound();
		for (i = nhni; i <= lsa; i+=3) { sound(i); delay(40); nosound(); } sound(lsa); delay(250); nosound(); delay(50); sound(nlsa); delay(300); nosound(); delay(150);

		sound(lsa); delay(250); nosound(); sound(hri); delay(250); nosound(); sound(lsa); delay(250); nosound(); sound(nlni); delay(250); nosound();
		for (i = nhni; i <= lsa; i+=3) { sound(i); delay(40); nosound(); } sound(lsa); delay(250); nosound();

		for (i = lsa; i <= lga; i+=6) { sound(i); delay(30); nosound(); } sound(lga); delay(250); nosound();

		sound(hri); delay(250); nosound(); sound(lga); delay(250); nosound(); sound(hri); delay(250); nosound(); sound(lsa); delay(250); nosound();

		for (i = lsa; i >= nhda; i-=3) { sound(i); delay(40); nosound(); } delay(750);
	}
	else if (music == TANKACE) {
		sound(pa); delay(400); nosound(); delay(300); sound(pa); delay(700); nosound(); delay(400);
		sound(npa); delay(75); nosound(); delay(100); sound(npa); delay(75); nosound(); delay(100); sound(npa); delay(75); nosound(); delay(100);
		sound(lsa); delay(75); nosound(); delay(100); sound(lsa); delay(75); nosound(); delay(100); sound(lsa); delay(75); nosound(); delay(100);
		sound(pa); delay(75); nosound(); delay(100); sound(pa); delay(75); nosound(); delay(100); sound(pa); delay(75); nosound(); delay(100);
		sound(hsa); delay(750); nosound(); sound(pa); delay(250); nosound();
	}
	nosound();
}
inline void playmusic (char music) {
	if (!sounds) return;
	if (music == SUCCESS) {
		sound(lsa); delay(100); nosound();
		sound(hga); delay(100); nosound();
		sound(pa); delay(100); nosound();
		sound(hsa); delay(300); nosound();
	}
	else if (music == FAILURE) {
		sound(npa); delay(100); nosound();
		sound(nlsa); delay(400); nosound();
	}
	else if (music == CRITERR) {
		sound(phri); delay(500); nosound(); delay(250);
		sound(phri); delay(500); nosound(); delay(250);
		sound(phri); delay(500); nosound(); delay(250);
		sound(phri); delay(500); nosound(); delay(250);
	}
	else if (music == COMP) {
		sound(hsa); delay(200); nosound(); sound(pa); delay(400); nosound();
	}
}
void display(char s[]) {
	for (int i = 0; s[i]; i++) { cout<<s[i]; flushall(); if (isalpha(s[i])) delay(50); else if (s[i] == '?' || s[i] == '!') delay(250); else if (s[i] == '.') delay(250); else if (s[i] == ',') delay(150); }
}
void writehighscore(unsigned long n, char wl, char diff) {
	clrscr();
	cout<<"\nEnter your name (not more than 15 characters): "; char s[26];
	int x = 0; char r;
	while (1) {
		r = getch();  if (r == 0) r = getc(stdin);
		if ((isgraph(r) || r == ' ' || r == '\t') && x < 15) { cout<<r; s[x] = r; x++; }
		else if (r == '\n' || r == '\r') if (x == 0) continue; else break;
		else if (r == '\b' && x > 0) { gotoxy(wherex()-1, wherey()); clreol(); x--; }
	}
	s[x] = 0;  ofstream fo ("hiscores.db", ios::app);
	encrypt(s); fo<<s<<'#'; if (diff == 'p') strcpy(s, "Pro!"); else strcpy(s, "Easy"); encrypt(s); fo<<s<<'#';
	struct date d; getdate(&d); s[0] = '0'+d.da_day/10; s[1] = '0'+d.da_day%10;
	s[2] = s[5] = '-'; s[3] = '0'+ d.da_mon/10; s[4] = '0'+d.da_mon%10; s[6] = 0;
	char yr	[5];
	itoa(d.da_year,yr, 10);  strcat(s,yr);
	cout<<"\n\nGame played on: "<<s; encrypt(s); fo<<s<<'#'; ultoa(n,s,10);
	encrypt(s); fo<<s<<'#';
	if (wl == 'w') strcpy(s, " WIN");
	else strcpy(s, "LOSS");  encrypt(s);
	fo<<s<<'#';
	cout<<"\n\n\nTHANK YOU FOR YOUR TIME! SEE YOU!";
	fo.close();  getch();
	_exit(0);
}
void gendb() {
	randomize();
	for (int i = 1; i <= 26; i++) {
		letters[i-1] = 'A' + i - 1;
		letters[25+i] = 'a' + i - 1;
	}
	ofstream fo ("ATLASLST.DB");
	if (!fo) { cout<<"\nLooks like there is some error creating the database file... Terminating for now..."; playmusic(CRITERR); getch(); _exit(0); }
	i = 0;  fo<<"RKEY:";  char c;   pwd[0] = '$'; int x = 1;
	while (++i <= 74) {
		c = 0;
		while (!isalpha(c)) c = letters[random(53)];
		fo<<c;
	} fo<<'S'; i = 0;
	while (++i <= 4) {
		c = 0;
		while (!isalpha(c)) c = letters[random(53)];
		fo<<c;
	} fo<<'s'; i = 0;
	while (++i <= 4) {
		c = 0;
		while (!isalpha(c)) c = letters[random(53)];
		fo<<c;
	} fo<<'d'; i = 0;
	while (++i <= 115) {
		c = 0;
		while (!isalpha(c)) c = letters[random(53)];
		fo<<c;
	} i = 0;
	while (++i <= 4) {
		c = 0;
		while (!isalpha(c)) c = letters[random(53)];
		pwd[x++] = c;
		fo<<c;
	}
	pwd[x] = 0;
	fo<<'$'; fo<<'\n';
	fo.close();
	cout<<"\n\nDatabase created successfully!\n";
	display("\nIMPORTANT NOTE: HIT ANY KEY TO VIEW ADMIN PASSWORD. THIS PASSWORD IS GENERATED ONCE ONLY, AND WILL HAVE TO BE USED TO ADD ENTRIES TO MY DATABASE. PLEASE MAKE NOTE OF THIS SOMEWHERE, AS THIS WILL NOT BE REVEALED TO YOU AGAIN!!!");
	getch(); cout<<"\n\nYOUR PASSWORD IS: "<<pwd; getch();
}
int pause() {
	ifstream fi ("Tmp.tmp");
	if (!fi) return 0;
	char s[100];
	while (fi.getline(s, 100, '\n')) if (strcmpi(s, "pausep") == 0 || strcmpi (s, "pausee") == 0) { fi.close(); return 1; }
	fi.close();
	return 0;
}
int alreadytold (char s[], char file[] = "Tmp.tmp") {
	ifstream fi (file);
	if (!fi) return 0;
	if (strcmpi(file, "ATLASLST.DB") == 0) {
		while (fi.get() != '$') if (fi.eof()) break;
		fi.get();
	}
	char s1[100]; fi.getline(s1, 100, '\n');
	while (!fi.eof()) {
		 if (strcmpi(s,s1) == 0) { fi.close(); return 1;}
		 fi.getline(s1, 100, '\n');
	}
	//if (strcmpi(s,s1) == 0) { fi.close(); delete s1; return 1; }
	fi.close(); return 0;
}
int isdiff (char s[]) {
	switch (tolower(s[strlen(s)-1])) {
		case 'y':
		case 'g':
		case 'n':
		case 'x':
		case 't':
		case 'h':
		case 'w': return 1;
		default: return 0;
	}
}
inline void add (char s[]) {
	ofstream fo ("Tmp.tmp", ios::app);
	fo<<s<<'\n';  fo.flush();
	fo.close();
}
void startgame() {
	clrscr();  unsigned regp = 0;
	ifstream fi ("ATLASLST.DB"); char s[100] = "\0", started = 0, difflevel, turn, e, paused = 0;
	long unsigned bg;
	if (!fi) { cout<<"\nDATABASE NOT FOUND! TERMINATING APP...";playmusic(CRITERR); getch(); _exit(0); }
	while (fi.get() != '$' && !fi.eof());
	if (fi.eof()) { cout<<"\nDATABASE EMPTY! TERMINATING APP...";playmusic(CRITERR); getch(); _exit(0); }
	fi.get(); bg = fi.tellg(); randomize();
	char r;
	if (pause()) {
		char start;
		if (!fi) { cout<<"\nTHE TEMP FILE HAS BEEN TAMPERED WITH OR IS MISSING! TERMINATING APP..."; playmusic(CRITERR); getch(); _exit(0); }
		display ("It looks like we have played a game before! Do you want to continue from where we left? (hit y/n). ");
		r = getch(); while (tolower(r) != 'y' && tolower(r) != 'n') r = getch();
		if (tolower(r) == 'n') { fi.close(); remove ("Tmp.tmp"); strcpy(database, "ATLASLST.DB"); fi.open("ATLASLST.DB"); paused = 0; }

		else {
			fi.close(); fi.open("Tmp.tmp");
			ofstream fo ("Tmp.123");
			start = fi.get(); paused = 1;
			fo<<start<<'\n';
			char s1[100];
			while (fi.getline(s,100)) {
				if (strcmpi(s, "pausep") && strcmpi(s, "pausee")) { fo<<s<<'\n'; strcpy(s1, s); }
				else break;
			}
			fo.close();
			remove("Tmp.tmp"); rename("Tmp.123", "Tmp.tmp");
			if (strcmpi(s, "pausep") == 0) difflevel = 'p';
			else difflevel = 'e';
			fi.close();
			e = tolower(s1[strlen(s1)-1]); paused = 1;
			clrscr();
			gotoxy(1,12); cout<<"________________________________GAME CONTINUED!___________________________________";
			gotoxy(1,23);
			cout<<"Computer: "<<s1;
			turn = 'p';
		}
		if (!fi) fi.open("ATLASLST.DB");
	}
	if (tolower(r) == 'n' || !paused) {
		if (!fi) fi.open("ATLASLST.DB");
		display ("Who do you think should start... you (hit '1') or me (hit '2') ?");
		char r = getch();
		while (r != '1' && r != '2') r = getch();
		if (r == '1') {turn = 'p';add("p"); } else {turn = 'c'; add("c"); }
		display ("\nDo you want to play in Easy Mode (hit 'e') or Pro Mode ? (hit 'p'). ");
		while (tolower(r) != 'p' && tolower(r) != 'e') r = getch();
		difflevel = tolower(r);
		e = 'a' + random(27);
	} if (!paused) clrscr(); else { gotoxy(1,1); clreol(); } char toughover = 0;
	fi.close(); fi.open("ATLASLST.DB");
	if (!fi) { cout<<"\nDATABASE NOT FOUND! TERMINATING APP..."; playmusic(CRITERR); getch(); _exit(0); }
       /*start game*/  if (turn == 'p') e = 0; char flag = 0;

       if (!paused) {	gotoxy(1,12);
		     if (turn == 'p') cout<<setw(55)<<"PLAYER CHOOSES TO START!!!\n\n";
		     else cout<<setw(50)<<"COMPUTER STARTS!!!\n\n";
       cout<<"_________________________________GAME START!___________________________________";  }
       strcpy(letters, ""); char b = 0, told = 0, u = 0; r = 0;
	while (1) {
		fi.seekg(bg); fi.clear(); e  = tolower(e);
		if (!fi) {cout<<"DATABASE NOT FOUND! TERMINATING APP..."; playmusic(CRITERR); getch(); _exit(0); }
			if (turn == 'c') {
				gotoxy(1,24); clreol();
				if (told) {gotoxy(1,1); delline(); gotoxy(1,25);}
				clreol(); gotoxy(1,25);
				if (told) { display("Computer: (thinking)"); told = 0; }
				else cout<<"Computer: (thinking)"; gotoxy(11,wherey());
				if (paused) { paused = 0; continue; }
				fi.getline(s,100);
				while (tolower(s[0]) != e && !fi.eof()) fi.getline(s,100); long unsigned bg1 = fi.tellg();
				for (b = 0; b < u; b++) {
					if (e == letters[b]) { difflevel = 'p'; break; }
					else difflevel = 'e';
				}
			if (difflevel == 'e') {
				while (tolower(s[0]) == e && !fi.eof()) {
					if (!alreadytold(s) && !isdiff(s)) break;
					else fi.getline(s,100,'\n');
				}
				if (fi.eof())
				if (started) {
					clrscr(); gotoxy(1,12);
					cout<<"\nWOW! LOOKS LIKE YOU HAVE FINALLY BEATEN ME! IT WAS NICE PLAYING WITH YOU! TO ENABLE ME TO PLAY BETTER, PLEASE DON'T FORGET TO ADD NEW REGIONS TO MY DATABASE! THANK YOU!";
					play(TANKACE);
					remove("Tmp.tmp"); getch();
					writehighscore(regp, 'w', difflevel);
				}
				else if (!started) {
					if (!flag) {
						e = 'a'; flag = 1; continue; }
					else if (flag && e < 'z') {
						cout<<"Oh no. I am searching for words desperately already!"; e++; continue; }
					else if (flag && e == 'z') {
						clrscr(); gotoxy(1,12);
						cout<<"\nWOW! LOOKS LIKE YOU HAVE FINALLY BEATEN ME! IT WAS NICE PLAYING WITH YOU! TO ENABLE ME TO PLAY BETTER, PLEASE DON'T FORGET TO ADD NEW REGIONS TO MY DATABASE! THANK YOU!";
						play(TANKACE);
						remove("Tmp.tmp"); getch();
						writehighscore(regp, 'w', difflevel);
					}
				} else;
				else if (tolower(s[0]) != e) {
					if (started && !r)
						if (!toughover) { cout<<"WOW! WHAT A PLAYER! YOU'VE ACTUALLY MADE ME LOOK FOR WORDS! LET ME TRY TO GIVE MY BEST HERE, THEN!"; playmusic(COMP); r = 1; difflevel = 'p'; delay(1000); continue; }
						else {
							clrscr(); gotoxy(1,12);
							cout<<"\nWOW! LOOKS LIKE YOU HAVE FINALLY BEATEN ME! IT WAS NICE PLAYING WITH YOU! TO ENABLE ME TO PLAY BETTER, PLEASE DON'T FORGET TO ADD NEW REGIONS TO MY DATABASE! THANK YOU!";
							play(TANKACE);
							remove("Tmp.tmp"); getch();
							writehighscore(regp, 'w', difflevel);
						}
				}
			}
			else if (difflevel == 'p') {
				if (!toughover) {
					fi.seekg(bg1);
				while (tolower(s[0]) == e && !fi.eof()) {
					if (!alreadytold(s) && isdiff(s)) break;
					else fi.getline(s,100);
				}
				if (tolower(s[0]) != e) {
					gotoxy(11,24); clreol(); gotoxy(1,24); clreol(); gotoxy(1, 24);
					printf("\nComputer: Oh my god... You are playing too good! Will I survive this game? ");
					delay(1000); letters[25+u] = e; u++;
					toughover = 1;
					continue;
				}
				}
				else {
					fi.seekg(bg1);
				while (tolower(s[0]) == e && !fi.eof()) {
					if (!alreadytold(s) && tolower(s[0]) == e) break;
					else fi.getline(s,100);
				}
				}
			}
			if (e && e == tolower(s[0]) && !alreadytold(s)) { gotoxy(11,24); started = 1; clreol(); add(s); cout<<"\nComputer: "<<s; clreol(); playmusic(COMP); if (b == -1) difflevel = 'p'; e = tolower(s[strlen(s)-1]); told = 1; turn = 'p'; continue; }
		}
		else if (turn == 'p') {
			gotoxy(1,1); delline(); delline();
			gotoxy(1,24); for (int i = 0; i < 80; i++) cout<<'_';
			cout<<"\nYour turn: \n";
			gets(s);
			if (strcmpi(s, "give up") == 0) {
						       for (i = 0; i < 5; i++) { gotoxy(1, 21+i); clreol(); }
						       gotoxy(1,24);
						       cout<<setw(77)<<"You: give up"<<'\n';
						       for (int i = 0; i < 80; i++) cout<<'_';
						       cout<<"\n\n\t\t\tExiting... (YAAY! I WON!)\n\n";
						       remove("Tmp.tmp");
						       fi.seekg(bg); fi.clear();
						       if (started) {
						       while (fi.getline(s, 100) && e != tolower(s[0]) && !fi.eof());
						       while (fi.getline(s,100) && e == tolower(s[0]) && !fi.eof())
								if (!alreadytold(s)) { cout<<"Oh, and by the way, you could have come up with the region '"<<s<<"' ! Anyways, both of us keep learning ;) "; break; }
						       play (SURVIVA);
						       }
							getch();
							fi.close();
							writehighscore(regp,'l', difflevel);
						       _exit(0);
			}
			else if (strcmpi(s, "exit") == 0) {
						       for (i = 0; i < 5; i++) { gotoxy(1, 21+i); clreol(); }
						       gotoxy(1,24);
						       cout<<setw(77)<<"You: exit"<<'\n';
						       for (int i = 0; i < 80; i++) cout<<'_';
						       cout<<"\n\n\t\t\tAborting game... Bye-bye!\n\n";
						       fi.close(); getch(); remove("Tmp.tmp");  _exit(0);
			}
			else if (strcmpi(s, "pause") == 0) {
				for (i = 0; i < 5; i++) { gotoxy(1, 21+i); clreol(); }
						       gotoxy(1,24);
						       cout<<setw(77)<<"You: pause"<<'\n';
						       ifstream tmp ("Tmp.tmp");
						       for (int i = 0; i < 80; i++) cout<<'_';
						       if (started) cout<<"\n\n\tOkay, this game will be continued next time you log in! Bye-bye!\n\n";
						       else { cout<<"\n\nThis game has just begun when you have decided to pause. Hence, we will play a new game next time! Bye-bye!\n\n";
								remove("tmp.tmp"); fi.close(); getch(); _exit(0);
						       }
						       fi.close(); getch(); if (difflevel == 'p') strcat(s, "p"); else strcat(s,"e"); add(s); _exit(0);
			}
			while (strlen(s) == 0) {gotoxy(1,1); insline(); gotoxy(1,25); clreol(); playmusic(FAILURE); gets(s); }
			if (!strcmpi(s, "p") || !strcmpi(s, "c")) {
				for (i = 0; i < 5; i++) { gotoxy(1, 21+i); clreol(); }
				gotoxy(1, wherey()-1); clreol(); gotoxy(1, wherey()+1);
				cout<<setw(77-strlen(s))<<"You: "<<s;
				cout<<"\nComputer: INVALID TOKEN DETECTED! PLEASE ENTER A CITY NAME ATLEAST 3 CHARACTERS LONG!\n";
				playmusic(FAILURE); continue;
			}
			else if (tolower(s[0]) == e && alreadytold(s)) {
				for (i = 0; i < 5; i++) { gotoxy(1, 21+i); clreol(); }
				gotoxy(1, wherey()-1); clreol(); gotoxy(1, wherey()+1);
				cout<<setw(77-strlen(s))<<"You: "<<s;
				cout<<"\nComputer: THAT WORD HAS ALREADY BEEN USED! PLEASE RETRY!\n";
				playmusic(FAILURE); continue;
			}
			else if (tolower(s[0]) != e && e != 0) {
				for (i = 0; i < 5; i++) { gotoxy(1, 21+i); clreol(); }
				cout<<setw(77-strlen(s))<<"You: "<<s;
				cout<<"\nComputer: INPUT REJECTED! PLEASE ENTER A WORD STARTING WITH '"<<e<<"',  NOT '"<<(char)tolower(s[0])<<"' !\n";
				playmusic(FAILURE); continue;
			}
			fi.close(); int t = alreadytold(s, "ATLASLST.DB");
			if (tolower(s[0]) == e && t) {
				started = 1; regp++;
				for (i = 0; i < 5; i++) { gotoxy(1, 21+i); clreol(); } gotoxy(1,wherey()-1);
				cout<<setw(77-strlen(s))<<"You: "<<s<<'\n';  gotoxy(1,1); delline();
				e = tolower(s[strlen(s)-1]); playmusic(SUCCESS);
				add(s); turn = 'c'; fi.open("ATLASLST.DB"); fi.seekg(bg);

			}
			else if (!started && t) {
				started = 1; regp++;
				for (i = 0; i < 5; i++) { gotoxy(1, 21+i); clreol(); } gotoxy(1,wherey()-1);
				cout<<setw(77-strlen(s))<<"You: "<<s<<'\n';  gotoxy(1,1); delline();
				e = tolower(s[strlen(s)-1]); playmusic(SUCCESS);
				add(s); turn = 'c'; fi.open("ATLASLST.DB"); fi.seekg(bg);

			}
			else if ((!t && !started) || (!t && tolower(s[0]) == e)) {
				for (i = 0; i < 5; i++) { gotoxy(1, 21+i); clreol(); }
				gotoxy(1,21); cout<<setw(77-strlen(s))<<"You: "<<s;
				cout<<"\n\nComputer: I haven't heard of any place called '"<<s<<"' ! Please enter a place we both know!";
				playmusic(FAILURE);
				fi.open("ATLASLST.DB");
				continue;
			}
		}
	}
}
void inserttodb(char[], char,char); 	long double tot = 0, ext = 0;
int getpwd(char pwd[9]) {
	ifstream dbase ("ATLASLST.DB"); if (!dbase) return 0;
	int x = 0;
			dbase.get();  char pass = 0;
				dbase.seekg(79); char s = dbase.get();
				if (s != 'S') {
					dbase.seekg(0, ios::end);}
				else pass++;
				dbase.seekg(84); s = dbase.get();
				if (s != 's') {dbase.seekg(0, ios::end);}
				else pass++;
				dbase.seekg(89); s = dbase.get();
				if (s != 'd') {dbase.seekg(0, ios::end);}
				else pass++; x = 90;
				while (dbase.get() != '$' && !dbase.eof() && ++x <= 205);
				dbase.get();
				if (x != 206) {
					pass = 0;
				}
				if (isalpha(dbase.get())) pass++;
				if (pass != 4) { cout<<"\nTHE DATABASE APPEARS TO BE CORRUPTED! PLEASE ADD NEW REGIONS FROM SCRATCH USING SECTION '2' UNDER THIS MENU! "; getch(); dbase.close(); return 0;  }
				else {
					pwd[0] = '$';
					dbase.seekg(205);  dbase.clear();
					x = 0;
					while (++x <= 4) pwd[x] = dbase.get();
					dbase.close();
				}
				pwd[x] = 0;
	return 1;
}
void encrypt (char s[]) {
	if (!getpwd(pwd)) { cout<<"\nENCRYPTION FAILED! TERMINATING APP..."; getch(); _exit(0); }
	for (int i = 0, x = 0; i < strlen(s); i++) {
		s[i] = s[i] + pwd[x];
		if (x == 8) x = 0;
		else x++;
	}
}
void decrypt (char s[]) {
		if (!getpwd(pwd)) { cout<<"\nDECRYPTION FAILED! TERMINATING APP..."; getch(); _exit(0); }
	for (int i = 0, x = 0; i < strlen(s); i++) {
		s[i] = s[i] - pwd[x];
		if (x == 8) x = 0;
		else x++;
	}
}
void showhighscores() {
	clrscr();
	ifstream fi ("HISCORES.DB");
	if (!fi) { cout<<"\nWell, all my high-score records are empty!! Why don't we play some games together before we check the high scores? "; getch(); return; }
	cout<<setw(48)<<"    SCORES TABLE\n"; flushall();
	for (int i = 0; i < 80; i++) cout<<"฿";      unsigned char c, s[26];
	cout<<"Sl. no.ณ"<<setw(19)<<" Player Name"<<setw(19)<<"ณ Play Date ณ"<<setw(20)<<"No. of regions saidณ"<<setw(13)<<" Game Result ณ";
	for (i = 1; i <= 7; i++) cout<<"อ"; cout<<"ุ";
	for (i = 1; i <= 25; i++) cout<<"อ"; cout<<"ุ";
	for (i = 1; i <= 11; i++) cout<<"อ"; cout<<"ุ";
	for (i = 1; i <= 19; i++) cout<<"อ"; cout<<"ุ";
	for (i = 1; i <= 13; i++) cout<<"อ"; cout<<"ุ";
	i = 1;
	while (fi.getline(s,26,'#')) {
		decrypt(s);
		if (i > 22) {
			gotoxy(1,25); clreol();
			cout<<"\tHit '1' to return to main menu, or hit any other key to continue..."; char r = getch();
			if (r == '1') {fi.close(); return; }
			gotoxy(1,25); clreol();
			gotoxy(1,25);
		}
		if (strlen(s) == 0) strcpy(s, "NA"); char t[5]; itoa (i, t, 10);
		cout<<setw(5)<<t; gotoxy(8, wherey()); cout<<"ณ"; /*slno*/
		cout<<setw(10)<<' '<<s<<' '; fi.getline(s,26,'#');
		decrypt(s); strupr(s); cout<<"("<<s<<")"; /*difflevel*/
		gotoxy(34, wherey()); fi.getline(s,26,'#'); cout<<"ณ"; decrypt(s);
		if (strlen(s) == 0) strcpy(s, "NA");
		cout<<setw(strlen(s))<<s;     gotoxy(46, wherey()); cout<<"ณ"; fi.getline(s,26,'#'); decrypt(s);
		if (strlen(s) == 0) strcpy(s, "NA");
		cout<<setw(12)<<s; gotoxy(66, wherey()); cout<<"ณ"; fi.getline(s,26,'#'); decrypt(s);
		if (strlen(s) == 0) strcpy(s, "NA");

		if (strcmpi(s, "LOSS") == 0) strcpy(s, "COMPUTER WON!");
		else strcpy(s, "PLAYER WON!");
		cout<<setw(strlen(s))<<s;
		if (wherex() != 1) gotoxy(80, wherey());
		else gotoxy(80, wherey()-1); cout<<"ณ";
			if (i > 22) {
			int t = i;
			gotoxy(1,25); clreol(); gotoxy(1,1);
			cout<<"Sl. no.ณ"<<setw(19)<<" Player Name"<<setw(19)<<"ณ Play Date ณ"<<setw(20)<<"No. of regions saidณ"<<setw(13)<<" Game Result ณ";
			for (i = 1; i <= 7; i++) cout<<"อ"; cout<<"ุ";
			for (i = 1; i <= 25; i++) cout<<"อ"; cout<<"ุ";
			for (i = 1; i <= 11; i++) cout<<"อ"; cout<<"ุ";
			for (i = 1; i <= 19; i++) cout<<"อ"; cout<<"ุ";
			for (i = 1; i <= 13; i++) cout<<"อ"; cout<<"ุ";
			gotoxy(80,24);   i = t;
		}
		i++;
		if (fi.eof()) break;
	}
	for (i = 1; i <= 80; i++) cout<<"อ"; getch();
}         void addfiles();
void adminsettings () {
	clrscr();
	ifstream db ("ATLASLST.DB");
	if (db) {
		if (!getpwd(pwd)) { cout<<"\nLooks like there was some problem with the database! Please delete it and re-add all the regions to it!!!"; getch(); return; }
		printf("\nENTER ADMIN PASSWORD: ");
		char s[26];
		int x = 0; char r;
		while (1) {
			r = getch();  if (r == 0) r = getc(stdin);
			if ((isgraph(r) || r == ' ' || r == '\t') && x < 9) { cout<<'*'; s[x] = r; x++; }
			else if (r == '\n' || r == '\r') if (x == 0) continue; else break;
			else if (r == '\b' && x > 0) { gotoxy(wherex()-1, wherey()); clreol(); x--; }
		}
		s[x] = 0;
			while (strcmp(s, pwd) && strcmp(s,"-1")) {
				printf("\n\n\nINVALID PASSWORD!!! TRY AGAIN, TYPE -1 FOR MAIN MENU. "); getch(); clrscr();
				cout<<"\nENTER ADMIN PASSWORD: ";
				x = 0;
				while (1) {
					r = getch();
					if (r == 0) r = getc(stdin);
					if (isgraph(r) && x < 9) { cout<<'*'; s[x] = r; x++; }
					else if (r == '\n' || r == '\r') if (x == 0) continue; else if (x) break;
					else if (r == '\b' && x > 0) { gotoxy(wherex()-1, wherey()); clreol(); x--; }
				}
				s[x] = 0;
			}


			if (strcmp(s, "-1") == 0) return;
	}
	char r; flushall();
	do {
	clrscr();
	cout<<"\nCHOOSE FROM THE OPTIONS BELOW: "
	    <<"\n\n1 - Add new regions to database\n"
	    <<"\n2 - Delete database\n"
	    <<"\n3 - Delete score database\n"
	    <<"\n4 - Return to main menu\n"
	    <<"\n\nMake your choice.";
	    r = getch(); while (r < '1' || r > '4') r = getch();
	    if (r == '1') addfiles();
	    else if (r == '2') { ifstream fi ("ATLASLST.DB");
		if (!fi) { cout<<"\nDATABASE FILE NOT FOUND! ABORTING DELETION!"; getch(); }
		else { clrscr(); cout<<"\nCONFIRM DELETION OF DATABASE? \n\n(WARNING: ALL DATA ENTRIES WILL BE LOST, FROM BOTH HISCORES.DB \nAND ATLASLST.DB!!!) Hit STRICTLY 'y' for yes, 'n' for no.";
			char y = getch();
			while (y != 'y' && y != 'n') y = getch();
			if (y == 'y') { fi. close(); remove("ATLASLST.DB"); remove("HISCORES.DB"); cout<<"\n\nDELETION OPERATION SUCCESSFUL!"; }
			else { cout<<"\nOperation aborted by user..."; }
		}
	    }
	    else if (r == '3') { ifstream fi ("HISCORES.DB");
		if (!fi) { cout<<"\nHISCORES.DB NOT FOUND! ABORTING DELETION!"; getch(); }
		else { clrscr(); cout<<"\nCONFIRM DELETION OF HIGHSCORES DATABASE? (WARNING: ALL DATA ENTRIES WILL BE LOST!!!) Hit STRICTLY 'y' for yes, 'n' for no.";
			char y = getch();
			while (y != 'y' && y != 'n') y = getch();
			if (y == 'y') { fi. close(); remove("HISCORES.DB"); cout<<"\n\nHISCORES.DB REMOVED SUCCESSFULLY!"; }
			else { cout<<"\n\n\nOperation aborted by user..."; }
		}
	    }
	    else if (r == '4') return;
	    getch();
	} while (r != '4');
}
void addfiles () {
	clrscr(); ext = tot = 0;
	char *ch = new char [100], dbflg, *d; int n; ifstream f;
	ifstream fi("ATLASLST.DB");
	if (!fi) { cout<<"\nLooks like there is no default database! Hit any key to create one. "; getch(); gendb(); cout<<"\nHit any key to continue."; dbflg = 1; getch(); }
	else {
		fi.get();  char pass = 0;
				fi.seekg(79); char s = fi.get();
				if (s != 'S') {
					fi.seekg(0, ios::end);}
				else pass++;
				fi.seekg(84); s = fi.get();
				if (s != 's') {fi.seekg(0, ios::end);}
				else pass++;
				fi.seekg(89); s = fi.get();
				if (s != 'd') {fi.seekg(0, ios::end);}
				else pass++; int x = 90;
				while (fi.get() != '$' && !fi.eof() && ++x <= 209);
				if (x != 209) {
					pass = 0;
				}   fi.seekg(210);  if (fi.eof()) fi.clear();
				fi.get();
				fi.get();  fi.get();
				if (!fi.get() ||!isalpha(fi.get())) pass = 0;
				else pass++;
				if (fi.eof()) { pass = 4; dbflg = 1; }
				if (pass != 4) {
					 cout<<"\nTHE DATABASE APPEARS TO BE CORRUPTED OR EMPTY! PLEASE ADD NEW REGIONS FROM SCRATCH USING SECTION '2' UNDER THIS MENU! ";
					 if (fi.eof()) cout<<"\nERRCODE: EOF";
					 else cout<<"\nERROR CODE: "<<(int)pass<<"_"<<fi.tellg();
					 getch(); fi.close(); return;
				}

		else dbflg = 0;

	}
		fi.close();
		clrscr();
		cout<<"\nWelcome to the 'Adding regions' section! \n\nHere you just tell me a file to read regions from, and I copy all of the non-duplicate entries into my database. ";
		cout<<"\n\n\nHow many files should I add from? Enter -1 to return to main menu. \nEnter here: ";
		cin>>ch; n = atoi(ch);
	if (n == -1) { delete ch; cout<<"\nHit any key to return..."; return; }
	while (n <= 0) {
		if (n == -1) { delete ch; return; }
		cout<<"\nINVALID NUMBER OF FILES ENTERED! PLEASE RETRY!\nEnter no. of files to extract regions from: ";
		cin>>ch; n = atoi(ch);
	}
	clrscr();
	char **files; d = new char [n];
	for (int i = 0; i < n; i++) {
		clrscr();
		cout<<"\nEnter the name of file "<<i+1<<": "; cin>>ch;
		ch[12] = 0;
		while (strlen(ch) > 8) { cout<<"\nINVALID FILE NAME! NAME SHOULD BE A MAXIMUM OF 8 CHARACTERS LONG!";
			cout<<"\nEnter the name of file "<<i+1<<": "; cin>>ch;
			ch[12] = 0;
		}
		fi.open(ch);
		while (!fi) {  cout<<"\nTHE FILE "<<ch<<" DOES NOT EXIST! PLEASE RETRY!";
			cout<<"\nEnter the name of file "<<i+1<<": "; cin>>ch; ch[12] = 0;
			fi.open(ch);
		}
		for (int t = 0; t < i; t++) {
			if (strcmpi(ch, files[t]) == 0) { t = -1; break; }
		}
		if (t == -1) { cout<<"\nTHAT FILE NAME HAS ALREADY BEEN ENTERED! PLEASE RETRY! "; getch(); fi.close(); i--; continue; }
		files[i] = new char [strlen(ch)+3]; ch[12] = 0;
		if (!files[i]) { cout<<"\nMEMORY ALLOCATION FAILURE! TERMINATING APP..."; getch(); _exit(0); }
		strcpy(files[i],ch);
		fi.close();
	}
	char *delim = new char [n];
	if (!delim) { cout<<"\nMEMORY ALLOCATION FAILURE! TERMINATING APP..."; getch(); _exit(0); }
       for (i = 0; i < n; i++) {
	clrscr();
	cout<<"\nChoose the option from below that best suits the way in which the data is stored in the file "<<files[i]<<": ";

	cout<<"\n1 - The regions are in delimiters, ignore everything outside the delimiters.";
	cout<<"\n2 - The regions are in a plain text file, each in one line (<enter> will be taken as new line). ";
	cout<<"\n3 - Exit.\n\nMake your choice: ";
	cin>>ch;
		if (strcmpi(ch, "3") == 0) { cout<<"\nExiting..."; getch(); delete files,d; return; }
	strcpy(database, "ATLASLST.DB");
	if (!strcmpi(ch, "1") || !strcmpi(ch,"2")) {
		if(strcmpi(ch,"1") == 0) {cout<<"\nEnter the delimiter: "; cin>>d[i];
			while (isalpha(d[i])) {
			cout<<"\nPlease enter a valid non-alphabetic delimiter!";
			cout<<"\nEnter the delimiter: "; cin>>d[i];
			}
		}
		else { d[i] = '\n'; }
	}
	}
	delete ch;
		for (i = 0; i < n; i++) { clrscr();  cout<<"\nPROGRESS: \nFILE "<<i+1<<" OF "<<n<<": "; inserttodb(files[i], d[i],dbflg); }
		  //delete d;
		  ofstream fo;  char s[100];
		  fo.open ("Tmpreg.txt"); fi.close(); fi.open("ATLASLST.DB");
		{
		if (!fi) { cout<<"\nDATABASE FILE NOT FOUND! CRITICAL ERROR! SHUTTING DOWN THE APP..."; getch(); _exit(0); }
		fi.seekg(0);int l = fi.get();
		while (l != '$') {fo<<(char)l; fi.get((unsigned char)l); }
		fo<<"$\n";
		fi.get((char)l);
		fi.close();
		}
		char file[7] = "\0";  file[0] = 'A'; strcat(file, ".txt");
		for (char l = 'A'; l <= 'Z'; l++) {
			file[0] = (char)l;
			 f.open("ATLASLST.DB");
				if (!f) { cout<<"\nDATABASE NOT FOUND! TERMINATING APP!"; getch(); _exit(0); }
				while (f.get() != '$' && !f.eof());
				if (f.eof()||f.get() != '\n') { cout<<"\nDATABASE CORRUPTED! TERMINATING APP!"; getch(); _exit(0); }
				f.getline(s,100);
				while (tolower(s[0]) != tolower(l) && !f.eof()) f.getline(s,100);
				while (tolower(s[0]) == tolower(l) && !f.eof()) { f.getline(s,100); fo<<s<<'\n'; fo.flush(); }
			f.close();
			f.open(file);
			if (!f) { cout<<"\nNo regions found starting with: "<<(char)l<<"."; continue; }
			else {
				f.seekg(0);
				while (f.getline(s, 100, '\n')) fo<<s<<'\n';
				f.close();
				cout<<"\nAdded all regions starting with: "<<(char)l<<".";
				fo.flush();
			}
			f.close(); remove(file);
		}
		fo.close();
		cout<<"\nAlmost there....";
		remove("ATLASLST.DB"); remove("TMP.123");
		cout<<"\n\nSummary:\n\n\nExtracted: "<<tot<<" region(s).\nAdded: "<<ext<<" region(s).";
		cout<<"\nThanks for taking the time to add the regions! I hope I will be able to play with you better! Please restart the app to get us playing!";
		getch();
		flushall();
		if (rename("TMPREG.TXT", "ATLASLST.DB")) {
		perror ("\n\nRename error: "); cout<<"\nFILE ADDING OPERATION FAILED UNEXPECTEDLY. EXITING...";
		getch(); _exit(0);
		}
}
void inserttodb(char ch[], char d, char dbflg) {
	long double ext = 0, tot = 0;
	cout<<'\n';
	for (int i = 0; i < 80; i++) cout<<'_'; cout<<'\n';
	char s[100];
	ifstream f;
		cout<<"\nInterpreting the file..Please wait....";
		{  f.open(ch);
		if (!f) {  cout<<"\nTHE FILE '"<<ch<<"' DOES NOT EXIST! EXITING!"; playmusic(CRITERR); getch(); _exit(0); }
		if (d != '\n') {
			while (f.get() != d && !f.eof());
			if (f.eof()) { cout<<"\nINVALID FILE! DELIMITER NOT FOUND IN THE FILE! ABORTING ADDING OPERATION FOR THIS FILE!"; getch(); return; }
			while (f.get() != d && !f.eof());
			if (f.eof()) { cout<<"\nINVALID FILE! DELIMITER NOT FOUND IN THE FILE! ABORTING ADDING OPERATION FOR THIS FILE!"; getch(); return; }
		}
		f.seekg(0, ios::end); long unsigned size = f.tellg();
		f.seekg(0, ios::beg); ofstream fo ("TMP.123");
		gotoxy(wherex()-3, wherey()+1);
		cout<<"Progress: "; int x = wherex();
		if (d == '\n') f.get();
		else while (f.get() != d && !f.eof());
		if (d != '\n' && f.eof()) { cout<<"\nNO SUITABLE RECORDS FOUND! ADDING FROM FILE ABORTED!"; f.close(); getch(); return; }
		if (d == '\n') f.seekg(0);

		while (!f.eof() && f.getline(s, 100,d)) {
			clreol(); gotoxy(x, wherey());
			cout<<f.tellg()*100/size<<" %";
			fo<<s<<'\n';
			if (d != '\n') while (f.get() != d && !f.eof());
			fo.flush();
			if (f.eof()) break;
		}
		gotoxy(1, wherey()); clreol(); strcpy(s,"");
		f.close(); fo.close(); f.open("TMP.123");
		}
		ofstream fo; cout<<'\n'; cout<<"Found: ";
		f.seekg(0, ios::end); int y = wherey(); gotoxy(7,y);
		long unsigned size = f.tellg();
		f.seekg(0,ios::beg); f.clear();
		tot = ext = 0;
		if (dbflg)
			while (f.getline(s,100,'\n')) {
			s[0] = toupper(s[0]);
			gotoxy(8,y); clreol();
			if (isspace(s[strlen(s)-1])) s[strlen(s)-1] = 0;
			char file[7] = "\0"; file[0] = s[0]; strcat(file, ".txt");
			for (int j = 0; i < strlen(s); j++) {
				while (isspace(s[j])) j++;
				if (s[j] == 0) { j = -1; break; }
			}
			for (int i = 0; i < strlen(s); i++) if (!isalpha(s[i]) && (s[i] != ' ' && s[i] != '\'' && i != 0)) { i = -1; break; }
			if (i == -1 || j == -1 || !isalpha(s[0])) {
				gotoxy(8,y);  clreol();
				cout<<s;
				cout<<"\nExtracted: "<<++tot<<" Added: "<<ext<<" Rejected: "<<tot-ext;
				cout<<"\nProgress: "<<(unsigned long)f.tellg()*100/size<<" %";
			}
			else if (strlen(s) == 0) {
				gotoxy(8,y); clreol();
				cout<<s;
				cout<<"\nExtracted: "<<++tot<<" Added: "<<ext<<" Rejected: "<<tot-ext;
				cout<<"\nProgress: "<<(unsigned long)f.tellg()*100/size<<" %";
			}
			else if (alreadytold(s, file)) {
				gotoxy(8,y);
				clreol();
				cout<<s;
				cout<<"\nExtracted: "<<++tot<<" Added: "<<ext<<" Rejected: "<<tot-ext;
				cout<<"\nProgress: "<<(unsigned long)f.tellg()*100/size<<" %";
			}
			else {
				fo.open (file, ios::app);
				s[0] = toupper(s[0]);
				for (int i = 0; i < strlen(s); i++) {
					if (isspace(s[i]) && i < strlen(s) - 1) {
						s[i] = ' ';
						s[i+1] = toupper(s[i+1]);
					}

				}
				fo<<s<<'\n';   fo.flush();
				fo.close();
				gotoxy(8, y); clreol();
				cout<<s;
				cout<<"\nExtracted: "<<++tot<<" Added: "<<++ext<<" Rejected: "<<tot-ext;
				cout<<"\nProgress: "<<(unsigned long)f.tellg()*100/size<<" %";
			}
			if (kbhit()) {
					int x = wherex(), y = wherey();
				       gotoxy(wherex()+3, wherey()+3);
				       cout<<"\nOperation paused. Hit 'y' to continue, or 'n' to stop.";
				       char r = getch();
				       while (tolower(r) != 'y' && tolower(r) != 'n') r = getch();
				       if (tolower(r) == 'y') { gotoxy(1, wherey()); clreol(); gotoxy(x,y); continue; }
				       else { cout<<"\nOperation aborted by user. Proceeding to add extractes files to database..."; delay(1000); break; }
			}
		}
		else {
			while (f.getline(s,100,'\n')) {	s[0] = toupper(s[0]);
				gotoxy(8,y); clreol();
				if (isspace(s[strlen(s)-1])) s[strlen(s)-1] = 0;
				char file[7] = "\0"; file[0] = s[0]; strcat(file, ".txt");
			for (int j = 0; i < strlen(s); j++) {
				while (isspace(s[j])) j++;
				if (s[j] == 0) { j = -1; break; }
			}
			for (int i = 0; i < strlen(s); i++) if (!isalpha(s[i]) && (s[i] != ' ' && s[i] != '\'' && i != 0)) { i = -1; break; }
			if (i == -1 || j == -1 || !isalpha(s[0])) {
				gotoxy(8,y);  clreol();
				cout<<s;
				cout<<"\nExtracted: "<<++tot<<" Added: "<<ext<<" Rejected: "<<tot-ext;
				cout<<"\nProgress: "<<(unsigned long)f.tellg()*100/size<<" %";
			}
			else if (strlen(s) == 0) {
				gotoxy(8,y); clreol();
				cout<<s;
				cout<<"\nExtracted: "<<++tot<<" Added: "<<ext<<" Rejected: "<<tot-ext;
				cout<<"\nProgress: "<<(unsigned long)f.tellg()*100/size<<" %";
			}
			else if (alreadytold(s, file) || alreadytold(s, "ATLASLST.DB")) {
				gotoxy(8,y);
				clreol();
				cout<<s;
				cout<<"\nExtracted: "<<++tot<<" Added: "<<ext<<" Rejected: "<<1+tot-ext;
				cout<<"\nProgress: "<<(unsigned long)f.tellg()*100/size<<" %";

			}
			else {
				{ifstream fi ("ATLASLST.DB");
				if (!fi) { clrscr();  cout<<"\nDATABASE '"<<database<<"' NOT FOUND! TERMINATING APP..."; playmusic(CRITERR); getch(); _exit(0); }
				fi.close();
				}
				fo.open (file, ios::app);
				s[0] = toupper(s[0]);
				for (int i = 0; i < strlen(s); i++) {
					if (isspace(s[i]) && i < strlen(s) - 1) {
						s[i] = ' ';
						s[i+1] = toupper(s[i+1]);
					}

				}
				fo<<s<<'\n';   fo.flush();
				fo.close();
				gotoxy(8, y); clreol();
				cout<<s;
				cout<<"\nExtracted: "<<++tot<<" Added: "<<++ext<<" Rejected: "<<tot-ext;
				cout<<"\nProgress: "<<(unsigned long)f.tellg()*100/size<<" %";
			}
			if (kbhit()) {
					int x = wherex(), y = wherey();
				       gotoxy(wherex()+3, wherey()+3);
				       cout<<"\nOperation paused. Hit 'y' to continue, or 'n' to stop.";
				       char r = getch();
				       while (tolower(r) != 'y' && tolower(r) != 'n') r = getch();
				       if (tolower(r) == 'y') { gotoxy(1, wherey()); clreol(); gotoxy(x,y); continue; }
				       else { cout<<"\nOperation aborted by user. Proceeding to add extractes files to database..."; delay(1000); break; }
			}
		}
		}
		f.close(); fo.close();
		::tot += tot; ::ext += ext;
}
void howtoplay(); char startflag = 0;
void main() {
	clrscr();
	if (!startflag) {cout<<"\nENABLE SOUNDS? (HIT 'Y' FOR YES, 'N' FOR NO). ";
	sounds = getch();
	while (tolower(sounds) != 'y' && tolower(sounds) != 'n') sounds = getch();
	if (sounds == 'y') sounds = 1;
	else sounds = 0;
	playmusic(COMP);
	}
	char *ch = (char *)(malloc(100));
		do {
			clrscr();
			if (!startflag) {
			gotoxy(1,21);
			for (int i = 1; i <= 68; i++) { gotoxy(i, wherey()); cout<<"CREATED BY:"; delay(10); gotoxy(1, wherey()); clreol(); } gotoxy(1,wherey()); cout<<setw(80)<<"CREATED BY:"; delay(500);
			for (i = 1; i <= 43; i++) { gotoxy(i, wherey()); cout<<"S SANDEEP OF CLASS XII - B, PSBB NGM"; delay(15); gotoxy(1, wherey()); clreol(); } gotoxy(1,wherey()); gotoxy(1,wherey()); cout<<setw(80)<<"S SANDEEP OF CLASS XII - B, PSBB NGM";
			for (i = 1; i <= 64; i++) { gotoxy(i, wherey()); cout<<"ROLL NO.: 120224"; delay(15); gotoxy(1, wherey()); clreol(); } gotoxy(1, wherey()); gotoxy(1, wherey()); cout<<setw(80)<<"ROLL NO.: 120224";
			for (i = 1; i <= 41; i++) { gotoxy(i, wherey()); cout<<"COMPUTER SCIENCE BOARD PROJECT 2017-18"; delay(15); gotoxy(1, wherey()); clreol(); } gotoxy(1, wherey()); cout<<setw(80)<<"COMPUTER SCIENCE BOARD PROJECT 2017-18"; delay(300);
			startflag = 1; gotoxy(1,1);
			}
			else {
			gotoxy(1, 21);
			cout<<setw(80)<<"CREATED BY:";
			cout<<setw(80)<<"S SANDEEP OF CLASS XII - B, PSBB NGM";
			cout<<setw(80)<<"ROLL NO.: 120224";
			cout<<setw(80)<<"COMPUTER SCIENCE BOARD PROJECT 2017-18";
			gotoxy(1,1);
			}
			cout<<"ุ";
			for (int i = 2; i <= 79; i++) cout<<"อ";  cout<<"ุ";
			cout<<"ณ"<<setw(60)<<"THE GAME OF ATLAS - Let's see who wins!"<<setw(19)<<"ณ";
			cout<<"ุ";
			for (i = 2; i <= 79; i++) cout<<"อ";   cout<<"ุ";
				cout<<setw(44)<<"ุออออออุ"<<"\n";
				cout<<setw(44)<<"ณ Menu ณ"; cout<<'\n';
				cout<<setw(44)<<"ุออออออุ"<<"\n";
				cout<<" 1 - Start playing!\n\n"
				    <<" 2 - Admin Settings\n\n"
				    <<" 3 - How to play\n\n"
				    <<" 4 - Show Score table\n\n"
				    <<" 5 - Exit\n\n"
				    <<"Make your choice: ";
			int t = wherey(), t1 = wherex();
			strcpy(ch, "\0");
			while (strlen(ch) == 0) { gotoxy (t1, t); gets(ch);  }

			if (strcmp(ch, "5") == 0) cout<<"\nTerminating app as per your request...";
			if (strcmp(ch, "4") == 0) showhighscores();
			if (strcmp(ch,"1") && strcmp(ch,"2") && strcmp(ch,"3") && strcmp(ch,"4") &&strcmp(ch,"5")) {
				display("\nInvalid choice! Please hit the keyboard to retry! ");
				playmusic(FAILURE); getch();
			}
			if (strcmp(ch, "3") == 0) howtoplay();
			else if (strcmp(ch, "1") == 0) {
				ifstream fi ("ATLASLST.DB");  int x = 0;
				if (!fi) { cout<<"\nDEFAULT DATABASE NOT FOUND! PLEASE LOOK FOR AN EXISTING FILE NAMED 'ATLASLST.DB' OR ADD A FEW REGIONS BY USING SECTION '2' UNDER THIS MENU! EXITING FOR NOW!"; playmusic(CRITERR); getch(); continue; }
				fi.get();  char pass = 0;
				fi.seekg(79); char s = fi.get();
				if (s != 'S') {
					fi.seekg(0, ios::end);}
				else pass++;
				fi.seekg(84); s = fi.get();
				if (s != 's') {fi.seekg(0, ios::end);}
				else pass++;
				fi.seekg(89); s = fi.get();
				if (s != 'd') {fi.seekg(0, ios::end);	 }
				else pass++; x = 90;
				while (fi.get() != '$' && !fi.eof() && ++x <= 209);
				if (x != 209) {
					pass = 0;
				}   fi.seekg(210);  if (fi.eof()) fi.clear();
				fi.get();
				fi.get();  fi.get();
				if (!fi.get() ||!isalpha(fi.get())) pass = 0;
				else pass++;
				if (pass != 4) {
					 cout<<"\nTHE DATABASE APPEARS TO BE CORRUPTED OR EMPTY! PLEASE ADD NEW REGIONS FROM SCRATCH USING SECTION '2' UNDER THIS MENU! ";
					 if (fi.eof()) cout<<"\nERRCODE: EOF";
					 else cout<<"\nERROR CODE: "<<(int)pass<<"_"<<fi.tellg();
					 getch(); fi.close();  }
				else {  fi.close(); startgame(); }
			}
			else if (strcmp(ch, "2") == 0) { playmusic(SUCCESS); adminsettings(); }

		} while (strcmp(ch, "5"));
	getch();
	free(ch); _exit(0);
}

void howtoplay() {
	struct time t; gettime (&t); clrscr();   int night = 0;
	if (t.ti_hour >= 21 || t.ti_hour <= 3) night = 1;
	cout<<"\nWell, hello there!";
	if (!night) display ("\b, and a very good");
	if ((int)t.ti_hour >= 4 && (int)t.ti_hour <= 11) {display(" morning to you, my dear user!"); }
	if ((int)t.ti_hour >= 12 && (int)t.ti_hour <= 15) { display (" afternoon to you, my dear user!"); }
	if ((int)t.ti_hour >= 16 && (int)t.ti_hour <= 19) { display (" evening to you, my dear user!"); }
	cout<<"\n\nBefore we take a tour of this simple-looking, but highly entertaining software, let me give you a tip first: ";
	cout<<"\n\nYou may hit '1'now in case you want to cancel the tutorial. Hit any other key to continue. ";
	char e = getch(); if (e == '1') { display ("\nWell, thank you for using the software. "); if (night) display ("\nGood night."); cout<<"\nSee you!"; getch(); main(); }
	clrscr();

	display ("\nAll right. So, before we begin... have you heard of word-building games ? \n(hit y/n)");
	e = getch(); while (toupper(e) != 'Y' && toupper(e) != 'N') e = getch();
	if (tolower(e) == 'y') {
		display("\nYou know, those word-building games where you say a word ending with a particular letter, and the other person you're playing with says another word starting with it... Yeah?");
		display ("\nThis is the same sort of game, but instead of any word, we say the name of a country, city, state, or union territory. Hit '1' to exit tutorial, or hit '2' to continue. ");
		e = getch();
		while (e != '1' && e != '2') e = getch();
		if (e == '1') {  display ("\nWell, thank you for using the software. "); if (night) display ("\nGood night."); cout<<"\nSee you!"; getch(); main(); }

	}
	else { display("\n\nSo... a word-building game is a game played by 2 people. The first player says a word. This word's ending letter should be used as the starting letter of the next word, which second player would say. This game goes on until one person is out of words. Then the other person is the winner. Simple, right? It should get quite clear through an example.");
			display ("\nThis is the same sort of game, but instead of any word, we say the name of a country, city, state, or union territory. Hit '1' to exit tutorial, or hit '2' to continue. ");
		e = getch();
		while (e != '1' && e != '2') e = getch();
		if (e == '1') {  display ("\nWell, thank you for using the software. "); if (night) display ("\nGood night."); cout<<"\nSee you!"; getch(); main(); _exit(0); }
	} clrscr();
		cout<<"\nAll right. So here's an example of how a game would look like: ";
		display("\n\n\nComputer: Amsterdam");
		delay(1000);
		cout<<setw(80)<<"\n\t\t\t\t\t\t\t\tYou: Mongolia";
		delay(1000);
		display("\nComputer: Azerbaijan");
		delay(1000);
		cout<<setw(80)<<"\n\t\t\t\t\t\t\t\tYou: Namibia";
		delay(1000);
		display("\nComputer: Abu Dhabi\n\t\t\t\t\t");
		gotoxy(40,wherey() + 1);
		cout<<'.'; delay(400);
		gotoxy(40,wherey() + 1);
		cout<<'.'; delay(400);
		gotoxy(40,wherey() + 1);
		cout<<'.'; delay(400);
		display("\nAnd so on.... Until one of us has used up all the names of the places. ");
		display("\nAnd beware, you cannot repeat words you have already used! I'm keeping track of all the places we both have said in a file. So, rest assured, I won't cheat! ;) ");
		display("\n\nOh, and a piece of very important info: \n1) The default database I will be using to play with you is a file called ATLASLST.DB. It will get created once you choose '2' in the main menu. \nThis database should not be deleted at any cost. If it is, I can't play with you, and you'll have to add cities from a new file. \n2) You can type 'give up', 'exit' or 'pause' anytime while playing the game if you want to give up, exit without saving the current game, or save and quit the game, to be played later! ");
		display("\n\nThat's it, folks! Try exploring the software now, because too much of theory is boring... :-)");
		if (night) { cout<<"\n\nAnd oh, wish you a good night!"; }
		getch();
		return;
}
