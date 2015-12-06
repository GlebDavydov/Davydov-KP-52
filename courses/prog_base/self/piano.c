#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<math.h>
#include<conio.h>

/*imperial march: {c, 1, 4,}, {c, 1, 4}, {c, 1, 4}, {a, 0, 4}, {e, 1, 2}, {c, 1, 4}, {a, 0, 4}, {e, 1, 2}, {c, 1, 4},
		{pause, 0, 8}, {g, 1, 4,}, {g, 1, 4,}, {g, 1, 4,}, {gd, 1, 4,}, {e, 1, 2}, {c, 1, 4}, {a, 0, 4}, {e, 1, 2}, {c, 1, 6}, 
		{pause, 0, 8}, {c, 1, 2}, {c, 2, 4}, {c, 1, 4,}, {pause, 0, 2}, {c, 1, 2}, {c, 2, 4}, {pause, 0, 2}, {h, 1, 4}, {b, 1, 2}, {a, 1, 2,}, {gd, 1, 2}, {a, 1, 6}, 
		{pause, 0, 6}, {c, 1, 2}, {f, 1, 4}, {e, 1, 2}, {dd, 1, 2}, {d, 1, 2}, {cd, 1, 2}, {d, 1, 6}, {pause, 0, 6}, {a, 0, 2},
		{c, 1, 4}, {a, 0, 4}, {e, 1, 2}, {c, 1, 4}, {a, 0, 4}, {e, 1, 2}, {c, 1, 4}, {a, 0, 4}, {e, 1, 2}, {c, 1, 6}, {pause, 0, 10}, {100, 0, 1}*/

/*Smahs Mouth - All Star: {c, 1, 4}, {pause, 1, 2}, {g, 1, 2}, {e, 1, 4}, {pause, 1, 2}, {e, 1, 4}, 
		{pause, 1, 2}, {d, 1, 2}, {c, 1, 4}, {pause, 1, 4}, {e, 1, 4}, {pause, 1, 2}, {f, 1, 2}, {e, 1, 2}, {f, 1, 2}, {e, 1, 2,}, {d, 1, 4}, {pause, 1, 4},
		{c, 1, 4}, {pause, 1, 2}, {g, 1, 2}, {e, 1, 2}, {e, 1, 2}, {e, 1, 2}, {d, 1, 2}, {c, 1, 2}, {c, 1, 2}, {a, 0, 4}, 
		{pause, 1, 2}, {g, 0, 6}, {pause, 1, 6}, {c, 1, 4}, {g, 1, 4}, {e, 1, 2}, {e, 1, 2}, {e, 1, 2}, {d, 1, 2}, {pause, 1, 2}, 
		{c, 1, 4}, {f, 1, 4}, {pause, 1, 2}, {e, 1, 2}, {e, 1, 2}, {d, 1, 2}, {d, 1, 4}, {pause, 1, 2,},
		{c, 1, 2}, {c, 1, 2}, {g, 1, 4}, {pause, 1, 2}, {e, 1, 2}, {e, 1, 2}, {d, 1, 4}, {pause, 1, 2},
		{c, 1, 2}, {c, 1, 2}, {d, 1, 4}, {pause, 1, 2}, {g, 0, 6}, {pause, 1, 6}, {100, 0, 1}*/	

int main(void){
enum notes{a, b, h, c, cd, d, dd, e, f, fd, g, gd, pause};
	struct music{
		int note;
		int octava;
		int length;
	}; 
	struct music piano[1000] = {{c, 1, 4}, {pause, 1, 2}, {g, 1, 2}, {e, 1, 4}, {pause, 1, 2}, {e, 1, 4}, 
		{pause, 1, 2}, {d, 1, 2}, {c, 1, 4}, {pause, 1, 4}, {e, 1, 4}, {pause, 1, 2}, {f, 1, 2}, {e, 1, 2}, {f, 1, 2}, {e, 1, 2,}, {d, 1, 4}, {pause, 1, 4},
		{c, 1, 4}, {pause, 1, 2}, {g, 1, 2}, {e, 1, 2}, {e, 1, 2}, {e, 1, 2}, {d, 1, 2}, {c, 1, 2}, {c, 1, 2}, {a, 0, 4}, 
		{pause, 1, 2}, {g, 0, 6}, {pause, 1, 6}, {c, 1, 4}, {g, 1, 4}, {e, 1, 2}, {e, 1, 2}, {e, 1, 2}, {d, 1, 2}, {pause, 1, 2}, 
		{c, 1, 4}, {f, 1, 4}, {pause, 1, 2}, {e, 1, 2}, {e, 1, 2}, {d, 1, 2}, {d, 1, 4}, {pause, 1, 2,},
		{c, 1, 2}, {c, 1, 2}, {g, 1, 4}, {pause, 1, 2}, {e, 1, 2}, {e, 1, 2}, {d, 1, 4}, {pause, 1, 2},
		{c, 1, 2}, {c, 1, 2}, {d, 1, 4}, {pause, 1, 2}, {g, 0, 6}, {pause, 1, 6}, {100, 0, 1}};
	for(int i = 0; i < 1000; i++){
		switch(piano[i].note){
			case c:
				Beep(131*pow(2, piano[i].octava), 125*piano[i].length);
				break;
			case cd:
				Beep(138*pow(2, piano[i].octava), 125*piano[i].length);
				break;
			case d:
				Beep(147*pow(2, piano[i].octava), 125*piano[i].length);
				break;
			case dd:
				Beep(155*pow(2, piano[i].octava), 125*piano[i].length);
				break;
			case e:
				Beep(165*pow(2, piano[i].octava), 125*piano[i].length);
				break;
			case f:
				Beep(175*pow(2, piano[i].octava), 125*piano[i].length);
				break;
			case fd:
				Beep(185*pow(2, piano[i].octava), 125*piano[i].length);
				break;
			case g:
				Beep(196*pow(2, piano[i].octava), 125*piano[i].length);
				break;
			case gd:
				Beep(208*pow(2, piano[i].octava), 125*piano[i].length);
				break;
			case a:
				Beep(220*pow(2, piano[i].octava), 125*piano[i].length);
				break;
			case b:
				Beep(233*pow(2, piano[i].octava), 125*piano[i].length);
				break;
			case h:
				Beep(247*pow(2, piano[i].octava), 125*piano[i].length);
				break;
			case pause:
				Sleep(250*piano[i].length);
				break;
			default:
				return 0;
				break;
		}
	}
	return 0;
}