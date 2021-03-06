#include "includes.h"

#include "common.h"
#include "frontend.h"
#include "util.h"
#include "wpa_ctrl.h"
#include "witui.h"

int
main(int argc, char* argv[]) {
    /* setup & scan wpa signals */
    char message[2048];
    ctrl_conn = wpa_ctrl_open(WPA_SUPPLICANT_PATH);
    if (!ctrl_conn) {
        printf("Could not get ctrl interface!\n");
        return -1;
    }
    wpa_cli_cmd_scan(ctrl_conn, message);
    wpa_cli_cmd_scan_results(ctrl_conn, message);
    /*  end of wpa signals */

    /* parse signal names */
    ssid wlist[SSID_NUM];
    int ssid_count = ssid_str(message, wlist);
    for (int i = 0; i < ssid_count; i++) {
        printf("%s: ", wlist[i].name);
        for (int j = 0; j < strlen(wlist[i].name); j++) {
            printf(" %02x", (unsigned char)wlist[i].name[j]);
        }
        printf("\n");
    }
    initscr();
    /* run this loop until user exits (returns zero) or the user refreshes menu (returns 1)
     * in while loop
     */
    do {
        wpa_cli_cmd_scan(ctrl_conn, message);
        wpa_cli_cmd_scan_results(ctrl_conn, message);
        ssid_count = ssid_str(message, wlist);
    } while (make_ssid_menu(wlist, ssid_count, ctrl_conn));

    endwin();

    wpa_ctrl_close(ctrl_conn);

    return 0;
}
