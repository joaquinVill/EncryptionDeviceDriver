#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    char *file_path = argv[1];

    char encrypted_file[512];
    snprintf(encrypted_file, sizeof(encrypted_file), "%s.encrypted", file_path);  
   
    char openssl_command[1024];
    snprintf(openssl_command, sizeof(openssl_command),
             "openssl pkeyutl -encrypt -pubin -inkey /home/joaquin/Documents/Project/public.key -in \"%s\" -out \"%s\"",
             file_path, encrypted_file);

    int run = system(openssl_command);
    
    if (run == 0){
        remove(file_path);
    }

    return 0;
}
