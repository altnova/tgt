//< main checks for counters and click/file_input events

ext I ITER;
ext I MAIN_IT;
ext I test_cnt[];

//<     *   *  *             * * *             *  *   *     >//
//<              cnt_upd(tm_cnt cnt_, I act)                >//
//<     *   *  *             * * *             *  *   *     >//
//<         add to all cnt_ counters star_time[act]         >//
//<     *   *  *             * * *             *  *   *     >//
ext V cnt_upd(tm_cnt cnt_, I num);								

//<     *   *  *             * * *             *  *   *     >//
//<                      cnt_check()                        >//
//<     *   *  *             * * *             *  *   *     >//
//<     if global counter cnt value has overflow, dog dat   >//
//<     and board images must be updated (decremented)      >//
//<     *   *  *             * * *             *  *   *     >//
ext V cnt_check();										

//<     *   *  *             * * *             *  *   *     >//
//<                       death()                           >//
//<     *   *  *             * * *             *  *   *     >//
//<      check conditions of dog death (finish program)     >//
//<     *   *  *             * * *             *  *   *     >//
//<         on success (dog die) return 1; else 0           >//
//<     *   *  *             * * *             *  *   *     >//
ext C death();											

//<     *   *  *             * * *             *  *   *     >//
//<                    event_check()                        >//
//<     *   *  *             * * *             *  *   *     >//
//<        check for user's input and click events          >//
//<         dog act and dat modify in some cases            >//
//<     *   *  *             * * *             *  *   *     >//
ext V event_check();									

//<     *   *  *             * * *             *  *   *     >//
//<                   set_main_action()                     >//
//<     *   *  *             * * *             *  *   *     >//
//<     sets what dog should do if there are no special     >//
//<     conditions;     dependent on dog dat                >//
//<     *   *  *             * * *             *  *   *     >//
ext C set_main_action();						
