#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAXLEN 80
#define EXTRA 5
/* 4 for field name "data", 1 for "=" */
#define MAXINPUT MAXLEN + EXTRA + 2
/* 1 for added line break, 1 for trailing NUL */
#define DATAFILE "/var/www/html/s.json"

void unencode(char *src, char *last, char *dest)
{
  for (; src != last; src++, dest++)
    if (*src == '+')
      *dest = ' ';
    else if (*src == '%')
    {
      int code;
      if (sscanf(src + 1, "%2x", &code) != 1)
        code = '?';
      *dest = code;
      src += 2;
    }
    else
      *dest = *src;
  /**dest = '\n';*/
  *dest = '&';
  *++dest = '\0';
}

int timeStamp()
{
  time_t rawtime;
  struct tm *timeinfo;

  time(&rawtime);
  timeinfo = localtime(&rawtime);

  char *foo = asctime(timeinfo); // verwijderd de \n\r die je bij de asctime() is.
  foo[strlen(foo) - 1] = 0;

  return foo;
}

int template(int teste, int tijd)
{
  strcat(teste, tijd);

  int init_size = strlen(teste);
  char delim[] = "&";

  char *ptr = strtok(teste, delim);
  char *test = strtok(NULL, delim);

  char tempy[250];
  sprintf(tempy, ",{\"name\":\"%s\",\"dink\":\"%s\",\"time\":\"%s\"}]", ptr, test + 5, tijd); // kan beter.

  strcpy(teste, tempy);

  return teste;
}

int filtercookie(char data[])
{
  int size = strlen(data);
  int en;
  char subbuff[50];
  int npath;

  for (size_t i = 0; i < size; i++)
  {
    if (data[i] == '&')
    {
      if (en == 1)
      {
        memcpy(subbuff, &data[i + 8], 49); // filtert de cookie tag weg
        subbuff[49] = '\0';

        sprintf(npath, "/var/www/html/%s.json", subbuff);
        return npath;
        en = 0;
      }
      en++;
    }
  }
  return npath;
}

int main(void)
{
  char *lenstr;
  char input[MAXINPUT], data[MAXINPUT];
  long len;
  int fname;

  printf("%s%c%c\n",
         "Content-Type:text/html;charset=iso-8859-1", 13, 10);
  printf("<TITLE>Response</TITLE>\n");
  lenstr = getenv("CONTENT_LENGTH");
  if (lenstr == NULL || sscanf(lenstr, "%ld", &len) != 1 || len > MAXLEN)
    printf("<P>Error in invocation - wrong FORM probably.");
  else
  {
    FILE *f;
    fgets(input, len + 1, stdin);
    unencode(input + EXTRA, input + len, data); // deleted '+ Extra' om 'naam=' te behouden.
    fname = filtercookie(data);                 /// mag er mischien uit
    if (fopen(fname, "r+") == 0)
    {
      f = fopen(fname, "w+");
      fputs("[{} ", f); // [{} zorgt voor een leeg element die niet zal tonen op de webpagina en
    }                   // zorgt ervoor dat de template niet aangepast moet worden voor de uitbreideing
    else
      f = fopen(fname, "r+");
    if (f == NULL)
      printf("<P>Sorry, cannot store your data.");
    else
    {
      int tijd = timeStamp();

      int feest = template(data, tijd);

      //////////////////////////////////////
      //https://www.tutorialspoint.com/c_standard_library/c_function_fseek.htm

      fseek(f, -1, SEEK_END); // zoekt het einde van de file en zet de cursor 1 positie achteruit.
      //////////////////////////////////////
      fputs(feest, f);
    }

    fclose(f);

    printf("<P>Thank you! Your contribution has been stored.");
  }
  return 0;
}