#include "telet.h"
#include "stdio.h"

void SDL_DrawChar(SDL_Simplewin *sw, cell *hex, fntrow fontdata[FNTCHARS][FNTHEIGHT], unsigned char chr, int ox, int oy);
void setDrawColor(SDL_Simplewin *sw, color c);
void setFlags(unsigned char code, flags *current);


int main(int argc, char **argv)
{
  cell hex[HT][WT];
  SDL_Simplewin sw;
  fntrow font[FNTCHARS][FNTHEIGHT];
  flags current;

  printf("STARTING TEST: \n" );
      if ( (argc != 2) )  {
        printf("ERROR: Incorrect usage:\nOnly 1 argument is required.\n");
      }

importCodes(argv[1], hex);
Neill_SDL_ReadFont(font, "m7fixed.fnt");
Neill_SDL_Init(&sw);
printCodes(&sw, hex, &current, font);

printf("print s\n" );

do{
      SDL_Delay(MILLISECONDDELAY);
      Neill_SDL_UpdateScreen(&sw);
      Neill_SDL_Events(&sw);
  }
  while(!sw.finished);
      atexit(SDL_Quit);
      return 0;
}


FILE *openFile(char *filename, char *mode)
{
  FILE *file = fopen(filename, mode);
    if (file == NULL) {
    printf("ERROR: unable to open file:\nCheck filename and path.\n");
  }
  return file;
}

void importCodes(char *filename, cell hex[25][40])
{
  FILE *fp = openFile(filename, "rb");
  int i, w, h;
  unsigned char temphex[HT][WT];
 w = 0; h = 0; i = 0;

  printf("file open\n");
  while (( i = fread ( &temphex, sizeof(unsigned char) ,1000, fp)) > 0) {
        for (h = 0; h < HT; h++) {
          for (w = 0; w < WT; w++) {
            hex[h][w].code = (temphex[h][w]-128);
            printf("%x", temphex[h][w]);
      }
  }
  fclose ( fp);
  }}


void changeFlags(flags *flag)
  {
    flag->frontcolor = w;
    flag->backcolor = z;
  }

  void setCellFlags(cell *c, flags *flag)
  {
    c->flag.frontcolor = flag->frontcolor;
    /*
    printf("Previous Flag Color after Conversion: %d\n",flag->frontcolor );
    printf("Current Flag Color after Conversion: %d\n",flag->frontcolor );

    */
    c->flag.backcolor = flag->backcolor;
  }


void printCodes(SDL_Simplewin *sw, cell hex[HT][WT], flags *current,  fntrow (*fontdata)[18])
  {
    int  w, h;
    w = 0; h = 0;

    printf("Command: Print Codes:\n" );
      for (h = 0; h < HT; h++) {

        changeFlags(current);

        for (w = 0; w < WT; w++) {
          setCellFlags(&hex[h][w], current);
          printf("FC:%d \n",hex[h][w].flag.frontcolor);
          setFlags(hex[h][w].code, current);
          SDL_DrawChar(sw, &hex[h][w], fontdata, hex[h][w].code, w*WT/2, h*HT);
        }
        printf("\n");
  }
}

void SDL_DrawChar(SDL_Simplewin *sw, cell *hex, fntrow fontdata[FNTCHARS][FNTHEIGHT], unsigned char chr, int ox, int oy)
{
   unsigned x, y;
   for(y = 0; y < FNTHEIGHT; y++){
      for(x = 0; x < FNTWIDTH; x++){
         if(fontdata[chr-FNT1STCHAR][y] >> (FNTWIDTH - 1 - x) & 1){
           /*
           printf("Draw color set\n" );
           */
          setDrawColor(sw, hex->flag.frontcolor);
          /*
          printf("DC %d\n",hex->flag.frontcolor );
          */
         }
         else{
          Neill_SDL_SetDrawColour(sw, 0, 0, 0);
         }
         SDL_RenderDrawPoint(sw->renderer, x + ox, y+oy);
      }
   }
}

void setDrawColor(SDL_Simplewin *sw, color c){

     /*
     printf("Grade is = %d\n", c );
*/
     switch(c) {
       /*yellow*/
        case 1 :
           Neill_SDL_SetDrawColour(sw, 255, 255, 0 );
           /*
           printf("set draw YELLOW\n");
           */
           break;
        case 2 :
           Neill_SDL_SetDrawColour(sw, 0, 0, 255);
           /*
           printf("set draw BLUE\n");
           */
           break;
        case 3 :
           Neill_SDL_SetDrawColour(sw, 255, 0, 0);
           /*
           printf("set draw RED\n");
           */
           break;
        case 4 :
           Neill_SDL_SetDrawColour(sw, 255, 0, 125);
           /*
           printf("set draw MAGENTA\n");
          */
           break;
        case 5 :
          Neill_SDL_SetDrawColour(sw, 0, 255, 255);
          /*
          printf("set draw CYAN\n");
          */
          break;
        default :
           Neill_SDL_SetDrawColour(sw, 255, 255, 255);

     }
}

void setFlags(unsigned char code, flags *current)
{

  printf("Printing Codes %d ",code);
  /*
  */
  switch ((colorCode) code) {

    /* Alphanumeric colour codes. */
  case redf:
      current->frontcolor = 3;
      /*
      printf("RED" );
      printf("current font color  %d\n",current->frontcolor );
      */
      break;

case yellowf:
    current->frontcolor = 1;
    /*
    printf("YELLOW" );
    printf("current font color  %d\n",current->frontcolor );
    */
    break;

case bluef:
    current->frontcolor = 2;
    /*
    printf("BLUE" );
    printf("current font color  %d\n",current->frontcolor );
    */
    break;

case magentaf:
    current->frontcolor = 4;
    /*
    printf("MAGENTA" );
    printf("current font color  %d\n",current->frontcolor );
    */
    break;

case cyanf:
    current->frontcolor = 5;
    /*
    printf("CYAN" );
    printf("current font color  %d\n",current->frontcolor );
    */
    break;

case whitef:
    current->frontcolor = 6;
    /*
    printf("WHITE" );
    printf("current font color  %d\n",current->frontcolor );
    */
    break;
    }}
