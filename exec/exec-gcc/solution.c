#include <unistd.h>

int is_empty(char s)
{
  return s == ' ' || s == '\t' || s == '\n';
}

const int BUFFER_SIZE = 4096;

const char *TMP =
    "gcc -o out.out -x c - <<eof\n#include <stdio.h>\nvoid main() { "
    "printf(\"%%d\\n\", (%s)); }\neof";

char *trim(char *s)
{
  int len = 0;
  char *start = s;
  while (is_empty(*s))
    s++;

  char *end = s + strlen(s) - 1;
  while (end > s && *end != '\n')
  {
    *end-- = '\0';
  }
  *end = '\0';
  return s;
}

int main(int argc, char const *argv[])
{
  char buffer[BUFFER_SIZE];
  int amount = read(0, buffer, BUFFER_SIZE);
  if (amount == -1)
  {
    return 0;
  }

  char *string = trim(buffer);
  if (*string == '\0')
  {
    return 0;
  }

  char template_buffer[BUFFER_SIZE];
  snprintf(template_buffer, BUFFER_SIZE, TMP, string);
  system(template_buffer);

  execl("./out.out", (char *)NULL);

  return 0;
}