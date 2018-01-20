#include "extension.h"

void printHex(cell hex[25][40], flags* current);
const char* colorEnum(enum color color);
void htmlSixel(cell *hex, int h, int w, sixels sixel, FILE *file);

int main(int argc, char **argv)
{
  flags current;
  cell hex[HT][WT];


  printf("BEGINNING PROGRAM!\n" );

  importCodes(argv[1], hex); /* Imports 1000 codes from ARGV1 into array of cell structs */
  testFunction(argc, argv[2], hex); /* Initializes testing from ARGV */
  printHex(hex, &current);

}



void printHex(cell hex[25][40], flags* current){
  int  w, h;
  sixels sixel;
  FILE *file  = fopen("testhtml.m7", "w");
  w = 0;h = 0;


  fprintf(file, "<table style=\"color: white; font-size: 14pt; width: 5%%;\" bgcolor=\"#000000\">\n");
  fprintf(file, "<tbody>");

          for (h = 0; h < HT; h++) {
            changeFlags(current);
             printf("<tr>\n" );
             fprintf(file, "<tr>\n");
             for (w = 0; w < WT; w++) {
               setFlags(hex[h][w].code, current);
               setCellFlags(&hex[h][w], current);
               setHold(&hex[h][w]);



if(hex[h][w].flag.mode == contiguous &&
  ((hex[h][w].code > a0 && hex[h][w].code<=bf)|| hex[h][w].code >= e0))
   {
     htmlSixel(&hex[h][w], h,  w, sixel, file);
/*
   fprintf(file, "   <td><svg width=\"16\" height=\"18\"><rect width=\"16\" height=\"18\" style=\"fill:%s;\" /> </svg> </td>\n",colorEnum(hex[h][w].flag.frontcolor) );
*/
   }

   else if(hex[h][w].flag.mode == separate &&
     ((hex[h][w].code >= a0 && hex[h][w].code<=bf)|| hex[h][w].code >= e0))
      {
      fprintf(file, "   <td><svg width=\"10\" height=\"12\"><rect width=\"10\" height=\"12\" style=\"fill:%s;\" /> </svg> </td>\n",colorEnum(hex[h][w].flag.frontcolor) );
      }
                 else if(hex[h][w].code <= a0 || hex[h][w].code >= 0xff){
                 printf("   <td>  </td>\n", hex[h][w].code);
                 fprintf(file, "   <td style=\"background-color: %s;\">  </td>\n" , colorEnum(hex[h][w].flag.backcolor));
                  }

                 else {
                     printf("   <td bgcolor=\"%s\">%c</td>\n", colorEnum(hex[h][w].flag.backcolor), hex[h][w].code -DIFF );
                     fprintf(file, "   <td style=\"color: %s; background-color: %s;\">%c</td>\n", colorEnum(hex[h][w].flag.frontcolor) , colorEnum(hex[h][w].flag.backcolor)  , hex[h][w].code - DIFF );
                      }
            }
        printf("</tr>\n" );
        fprintf(file, "</tr>\n");
}
  fprintf(file, "</tbody>");
  fprintf(file, "</table>");

fclose(file);
}


void htmlSixel(cell *hex, int h, int w, sixels sixel, FILE *file){
      setSixels(hex->code,  &sixel);
fprintf(file, "  <td>\n <svg width=\"16\" height=\"18\">\n");


      if(sixel.uleft == true){
        fprintf(file, "   <rect width=\"8\" height=\"6\" x=\"0\" y=\"0\" style=\"fill:%s;\"/>\n",colorEnum(hex->flag.frontcolor) );
      }
      if(sixel.uright == true){
                fprintf(file, "   <rect width=\"8\" height=\"6\" x=\"8\" y=\"0\" style=\"fill:%s;\"/>\n",colorEnum(hex->flag.frontcolor) );
      }

      if(sixel.mleft == true){
        fprintf(file, "   <rect width=\"8\" height=\"6\" x=\"0\" y=\"6\" style=\"fill:%s;\"/>\n",colorEnum(hex->flag.frontcolor) );
      }

      if(sixel.mright == true){
        fprintf(file, "   <rect width=\"8\" height=\"6\" x=\"8\" y=\"6\" style=\"fill:%s;\"/>\n",colorEnum(hex->flag.frontcolor) );
      }

      if(sixel.bleft == true){
        fprintf(file, "   <rect width=\"8\" height=\"6\" x=\"0\" y=\"12\" style=\"fill:%s;\"/>\n",colorEnum(hex->flag.frontcolor) );
      }

      if(sixel.bright == true){
        fprintf(file, "   <rect width=\"8\" height=\"6\" x=\"8\" y=\"12\" style=\"fill:%s;\"/>\n",colorEnum(hex->flag.frontcolor) );
      }
  fprintf(file, "</svg></td>\n");
      resetSixels(&sixel);
  }


/*
<svg width="16" height="18">
<rect width="8" height="6" style="fill:rgb(0,255,255);stroke:rgb(0,0,0)" />
<rect width="8" height="6" x="8" y="6" style="fill:rgb(0,0,255);stroke-width:3 stroke:rgb(0,0,0)" />
<rect width="8" height="6" x="0" y="12" style="fill:rgb(0,0,255);stroke-width:3 stroke:rgb(0,0,0)" />

</svg>
*/











const char* colorEnum(enum color color)
{
   switch (color)
   {
      case red: return "red";
      case blue: return "blue";
      case yellow: return "yellow";
      case green: return "green";
      case cyan: return "cyan";
      case magenta: return "magenta";
      case white: return "white";
      case black: return "black";

   }
}
