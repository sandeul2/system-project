#include <stdio.h>
#include <sys/prctl.h>
#include <signal.h>
#include <sys/time.h>
#include <time.h>

#include <system_server.h>
#include <gui.h>
#include <input.h>
#include <web_server.h>

static int five_timer = 0;

static void five_timer_handler() {
    five_timer += 5;
    printf("five_timer is : %d\n", five_timer);
}

int posix_sleep_ms(unsigned int timeout_ms) {
    struct timespec sleep_time;

    sleep_time.tv_sec = timeout_ms / MILLISEC_PER_SECOND;
    sleep_time.tv_nsec = (timeout_ms % MILLISEC_PER_SECOND) * (NANOSEC_PER_USEC * USEC_PER_MILLISEC);

    return nanosleep(&sleep_time, NULL);
}

int system_server() {
    struct itimerspec ts;
    struct sigaction  sa;
    struct sigevent   sev;
    timer_t *tidlist;

    printf("나 system_server 프로세스!\n");

    /* lab6 : 시그널 타이머 핸들러*/
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = five_timer_handler; // five_timer 핸들러
    if (sigaction(SIGALRM, &sa, NULL) == -1) { // signal 함수로도 가능
        printf("sigaction");
        return 0;
    }

    /* lab6 : 5초 타이머를 만들어 봅시다. */
    struct itimerval itv;
    itv.it_interval.tv_sec = 5; // 5초 간격으로 반복
    itv.it_interval.tv_usec = 0; // 마이크로 단위 반복
    itv.it_value.tv_sec = 5; // 5초 후 타이머 시작
    itv.it_value.tv_usec = 0; // 마이크로 타이머 초기 설정
    setitimer(ITIMER_REAL, &itv, NULL);

    while (1) {
        posix_sleep_ms(5000);
    }

    return 0;
}

int create_system_server() {
    pid_t systemPid;
    const char *name = "system_server";

    printf("여기서 시스템 프로세스를 생성합니다.\n");

    /* lab2 : fork 를 이용하세요 */
    switch (systemPid = fork()) {
    case -1:
        printf("fork failed\n");
    case 0:
        /* lab2 : 프로세스 이름 변경 */
        if (prctl(PR_SET_NAME, (unsigned long) name) < 0)
            perror("prctl()");
        system_server(); // system_server 실행
        break;
    default:
        break;
    }

    return 0;
}
