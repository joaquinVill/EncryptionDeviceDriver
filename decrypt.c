#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    char *encrypted_file = argv[1];

    char decrypted_file[512];
    snprintf(decrypted_file, sizeof(decrypted_file), "%s.decrypted", encrypted_file);  
   
    char openssl_command[1024];
    snprintf(openssl_command, sizeof(openssl_command),
             "openssl pkeyutl -decrypt -inkey /home/joaquin/Documents/Project/private.key -in \"%s\" -out \"%s\"",
             encrypted_file, decrypted_file);

    int run = system(openssl_command);

    if (run == 0){
        remove(encrypted_file);
    }

    return 0;
}
