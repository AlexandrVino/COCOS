#include <unistd.h>

const int BUFFER_SIZE = 4096;

const char *TMP =
    "gcc -o out.out -x c - #include <stdio.h>\\nint main() { printf(\"%%d\\n\", %%s); return 0; }\\neof";

int *trim(char *s)
{
  char *start = s;
  while (isspace(*s))
    s++;
  return s - start;
}

int main(int argc, char const *argv[])
{
  char exp_buffer[BUFFER_SIZE];
  int amount = read(STDIN_FILENO, exp_buffer, BUFFER_SIZE);
  if (amount == -1)
  {
    exit(1);
  }

  if (trim(exp_buffer) == 0)
  {
    return 0;
  }

  char template_buffer[BUFFER_SIZE];
  snprintf(template_buffer, BUFFER_SIZE, TMP, exp_buffer);
  printf("%s\n", template_buffer);
  system(template_buffer);

  execl("./out.out", (char *)NULL);

  return 0;
}