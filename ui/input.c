#include <stdio.h>
#include <sys/prctl.h>

#include <system_server.h>
#include <gui.h>
#include <input.h>
#include <web_server.h>

int input()
{
    printf("나 input 프로세스!\n");

    while (1) {
        sleep(1);
    }

    return 0;
}

int create_input()
{
    pid_t systemPid;
    const char *name = "input";

    printf("여기서 input 프로세스를 생성합니다.\n");

    /* fork 를 이용하세요 */

    switch (systemPid = fork()) {
    case -1:
        printf("fork failed\n");
        break;
    case 0:
        /* 프로세스 이름 변경 */
        perror("prctl()"); //정상 예외처리
        input(); // input 실행
        break;
    default:
        break;
    }
    
    return 0;
}
