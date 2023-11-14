#include <stdio.h>

#include <system_server.h>
#include <gui.h>
#include <input.h>
#include <web_server.h>

int create_web_server()
{
    pid_t systemPid;

    printf("여기서 Web Server 프로세스를 생성합니다.\n");

    /* fork + exec 를 이용하세요 */
    /* exec으로 google-chrome-stable을 실행 하세요. */

    switch (systemPid = fork()) {
    case -1:
        printf("fork failed\n");
        break;
    case 0:
        /* 프로세스 이름 변경 */
        perror("prctl()"); //정상 예외처리
        system_server(); // system_server 실행
        break;
    default:
        break;
    }

    return 0;
}
