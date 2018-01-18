#define SUPER_START_LETTER 65
#define LOWER_START_LETTER 97

int validate_key(const char *str);

char * encrypt(char *str, const char *key);

int get_alpha_number(char letter);

int get_start_asci_number(char letter);

char get_asci(int shift, int super);
