

void S9xProcessEvents(bool block) {
    SDL_Event event;

    while (block && SDL_PollEvent(&event)) {
        switch (event.type) {
#ifdef CAANOO
                // CAANOO -------------------------------------------------------------
            case SDL_JOYBUTTONDOWN:
                keyssnes = SDL_JoystickOpen(0);
                //QUIT Emulator
                if (SDL_JoystickGetButton(keyssnes, sfc_key[QUIT]) && SDL_JoystickGetButton(keyssnes, sfc_key[B_1])) {
                    S9xExit();
                }// MAINMENU
                else if (SDL_JoystickGetButton(keyssnes, sfc_key[QUIT])) {
                    S9xSetSoundMute(TRUE);
                    menu_loop();
                    S9xSetSoundMute(FALSE);
                }
                break;

            case SDL_JOYBUTTONUP:
                keyssnes = SDL_JoystickOpen(0);
                switch (event.jbutton.button) {
                }
                break;
#else
                //PANDORA & DINGOO ------------------------------------------------------
            case SDL_KEYDOWN:
                keyssnes = SDL_GetKeyState(NULL);

                // shortcut
#ifdef PANDORA
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    S9xExit();
                }
#endif

#ifdef PANDORA
                if (event.key.keysym.sym == SDLK_s) {
                    do {
                        g_scale = (blit_scaler_e) ((g_scale + 1) % bs_max);
                    } while ((blit_scalers [ g_scale ].valid == bs_invalid)
                            || (Settings.SupportHiRes && !(blit_scalers [ g_scale ].support_hires)));
                    S9xDeinitDisplay();
                    S9xInitDisplay(0, 0);
                }
#endif //PANDORA
                //QUIT Emulator
                if ((keyssnes[sfc_key[SELECT_1]] == SDL_PRESSED) && (keyssnes[sfc_key[START_1]] == SDL_PRESSED) && (keyssnes[sfc_key[X_1]] == SDL_PRESSED)) {
                    S9xExit();
                }//RESET ROM Playback
                else if ((keyssnes[sfc_key[SELECT_1]] == SDL_PRESSED) && (keyssnes[sfc_key[START_1]] == SDL_PRESSED) && (keyssnes[sfc_key[B_1]] == SDL_PRESSED)) {
                    //make sure the sram is stored before resetting the console
                    //it should work without, but better safe than sorry...
                    Memory.SaveSRAM(S9xGetFilename(".srm"));
                    S9xReset();
                }//SAVE State
                else if ((keyssnes[sfc_key[START_1]] == SDL_PRESSED) && (keyssnes[sfc_key[R_1]] == SDL_PRESSED)) {
                    //extern char snapscreen;
                    char fname[256], ext[20];
                    S9xSetSoundMute(true);
                    sprintf(ext, ".00%d", SaveSlotNum);
                    strcpy(fname, S9xGetFilename(ext));
                    S9xFreezeGame(fname);
                    capt_screenshot();
                    sprintf(ext, ".s0%d", SaveSlotNum);
                    strcpy(fname, S9xGetFilename(ext));
                    save_screenshot(fname);
                    S9xSetSoundMute(false);
                }//LOAD State
                else if ((keyssnes[sfc_key[START_1]] == SDL_PRESSED) && (keyssnes[sfc_key[L_1]] == SDL_PRESSED)) {
                    char fname[256], ext[8];
                    S9xSetSoundMute(true);
                    sprintf(ext, ".00%d", SaveSlotNum);
                    strcpy(fname, S9xGetFilename(ext));
                    S9xLoadSnapshot(fname);
                    S9xSetSoundMute(false);
                }// MAINMENU
                else if ((keyssnes[sfc_key[SELECT_1]] == SDL_PRESSED) && (keyssnes[sfc_key[B_1]] == SDL_PRESSED)) {
                    S9xSetSoundMute(true);
                    menu_loop();
                    S9xSetSoundMute(false);
#ifdef DINGOO
                    //S9xSetMasterVolume (vol, vol);
                    gp2x_sound_volume(vol, vol);
#endif

#ifdef PANDORAKEYS
                }// another shortcut I'm afraid
                else if (event.key.keysym.sym == SDLK_SPACE) {
                    S9xSetSoundMute(true);
                    menu_loop();
                    S9xSetSoundMute(false);
                    //S9xSetMasterVolume (vol, vol);
                } else if (event.key.keysym.sym == SDLK_t) {
                    Settings.TurboMode = !Settings.TurboMode;
#endif //PANDORA
                }
                break;
            case SDL_KEYUP:
                keyssnes = SDL_GetKeyState(NULL);

                break;
#endif //CAANOO
        }
    }
}

void S9xInitInputDevices() {
#ifdef CAANOO
    keyssnes = SDL_JoystickOpen(0);
#else
    keyssnes = SDL_GetKeyState(NULL);
#endif

    memset(sfc_key, 0, 256);

#ifdef CAANOO
    // Caanoo mapping
    sfc_key[A_1] = CAANOO_BUTTON_B; //Snes A
    sfc_key[B_1] = CAANOO_BUTTON_X; //Snes B
    sfc_key[X_1] = CAANOO_BUTTON_Y; //Snes X
    sfc_key[Y_1] = CAANOO_BUTTON_A; //Snes Y
    sfc_key[L_1] = CAANOO_BUTTON_L;
    sfc_key[R_1] = CAANOO_BUTTON_R;
    sfc_key[START_1] = CAANOO_BUTTON_HELP1;
    sfc_key[SELECT_1] = CAANOO_BUTTON_HELP2;
    sfc_key[LEFT_1] = CAANOO_BUTTON_LEFT;
    sfc_key[RIGHT_1] = CAANOO_BUTTON_RIGHT;
    sfc_key[UP_1] = CAANOO_BUTTON_UP;
    sfc_key[DOWN_1] = CAANOO_BUTTON_DOWN;

    sfc_key[QUIT] = CAANOO_BUTTON_HOME;
#elif PANDORA
    // Pandora mapping
    sfc_key[A_1] = SDLK_END; //DINGOO_BUTTON_A; A = B
    sfc_key[B_1] = SDLK_PAGEDOWN; //DINGOO_BUTTON_B; B = X
    sfc_key[X_1] = SDLK_PAGEUP; //DINGOO_BUTTON_X; X = Y
    sfc_key[Y_1] = SDLK_HOME; //DINGOO_BUTTON_Y; Y = A
    sfc_key[L_1] = SDLK_RSHIFT; //DINGOO_BUTTON_L;
    sfc_key[R_1] = SDLK_RCTRL; // DINGOO_BUTTON_R;
    sfc_key[START_1] = SDLK_LALT; //DINGOO_BUTTON_START;
    sfc_key[SELECT_1] = SDLK_LCTRL; //DINGOO_BUTTON_SELECT;
    sfc_key[LEFT_1] = SDLK_LEFT; //DINGOO_BUTTON_LEFT;
    sfc_key[RIGHT_1] = SDLK_RIGHT; //DINGOO_BUTTON_RIGHT;
    sfc_key[UP_1] = SDLK_UP; //DINGOO_BUTTON_UP;
    sfc_key[DOWN_1] = SDLK_DOWN; //DINGOO_BUTTON_DOWN;
    /*
            // for now, essentially unmapped
            sfc_key[LEFT_2] = SDLK_g;
            sfc_key[RIGHT_2] = SDLK_j;
            sfc_key[UP_2] = SDLK_u;
            sfc_key[DOWN_2] = SDLK_n;
            sfc_key[LU_2] = SDLK_y;
            sfc_key[LD_2] = SDLK_b;
            sfc_key[RU_2] = SDLK_i;
            sfc_key[RD_2] = SDLK_m;

            sfc_key[QUIT] = SDLK_ESCAPE;
            sfc_key[ACCEL] = SDLK_TAB;
     */
#elif DINGOO
    // Dingoo mapping
    sfc_key[A_1] = DINGOO_BUTTON_A;
    sfc_key[B_1] = DINGOO_BUTTON_B;
    sfc_key[X_1] = DINGOO_BUTTON_X;
    sfc_key[Y_1] = DINGOO_BUTTON_Y;
    sfc_key[L_1] = DINGOO_BUTTON_L;
    sfc_key[R_1] = DINGOO_BUTTON_R;
    sfc_key[START_1] = DINGOO_BUTTON_START;
    sfc_key[SELECT_1] = DINGOO_BUTTON_SELECT;
    sfc_key[LEFT_1] = DINGOO_BUTTON_LEFT;
    sfc_key[RIGHT_1] = DINGOO_BUTTON_RIGHT;
    sfc_key[UP_1] = DINGOO_BUTTON_UP;
    sfc_key[DOWN_1] = DINGOO_BUTTON_DOWN;
    /*
            // for now, essentially unmapped
            sfc_key[LEFT_2] = SDLK_g;
            sfc_key[RIGHT_2] = SDLK_j;
            sfc_key[UP_2] = SDLK_u;
            sfc_key[DOWN_2] = SDLK_n;
            sfc_key[LU_2] = SDLK_y;
            sfc_key[LD_2] = SDLK_b;
            sfc_key[RU_2] = SDLK_i;
            sfc_key[RD_2] = SDLK_m;

            sfc_key[QUIT] = SDLK_d;
            sfc_key[ACCEL] = SDLK_u;
     */
#endif

    int i = 0;
    char *envp, *j;
    envp = j = getenv("S9XKEYS");
    if (envp) {
        do {
            if (j = strchr(envp, ','))
                *j = 0;
            if (i == 0) sfc_key[QUIT] = atoi(envp);
            else if (i == 1) sfc_key[A_1] = atoi(envp);
            else if (i == 2) sfc_key[B_1] = atoi(envp);
            else if (i == 3) sfc_key[X_1] = atoi(envp);
            else if (i == 4) sfc_key[Y_1] = atoi(envp);
            else if (i == 5) sfc_key[L_1] = atoi(envp);
            else if (i == 6) sfc_key[R_1] = atoi(envp);
            else if (i == 7) sfc_key[START_1] = atoi(envp);
            else if (i == 8) sfc_key[SELECT_1] = atoi(envp);
            else if (i == 9) sfc_key[LEFT_1] = atoi(envp);
            else if (i == 10) sfc_key[RIGHT_1] = atoi(envp);
            else if (i == 11) sfc_key[UP_1] = atoi(envp);
            else if (i == 12) sfc_key[DOWN_1] = atoi(envp);
            /*			else if (i == 13) sfc_key[LU_2] = atoi(envp);
                                    else if (i == 14) sfc_key[LD_2] = atoi(envp);
                                    else if (i == 15) sfc_key[RU_2] = atoi(envp);
                                    else if (i == 16) sfc_key[RD_2] = atoi(envp);
             */ envp = j + 1;
            ++i;
        } while (j);
    }

}


uint32 S9xReadJoypad(int which1) {
    uint32 val = 0x80000000;

    if (which1 > 4)
        return 0;

#ifdef CAANOO
    //player1
    if (SDL_JoystickGetButton(keyssnes, sfc_key[L_1])) val |= SNES_TL_MASK;
    if (SDL_JoystickGetButton(keyssnes, sfc_key[R_1])) val |= SNES_TR_MASK;
    if (SDL_JoystickGetButton(keyssnes, sfc_key[X_1])) val |= SNES_X_MASK;
    if (SDL_JoystickGetButton(keyssnes, sfc_key[Y_1])) val |= SNES_Y_MASK;
    if (SDL_JoystickGetButton(keyssnes, sfc_key[B_1])) val |= SNES_B_MASK;
    if (SDL_JoystickGetButton(keyssnes, sfc_key[A_1])) val |= SNES_A_MASK;
    if (SDL_JoystickGetButton(keyssnes, sfc_key[START_1])) val |= SNES_START_MASK;
    if (SDL_JoystickGetButton(keyssnes, sfc_key[SELECT_1])) val |= SNES_SELECT_MASK;
    if (SDL_JoystickGetAxis(keyssnes, 1) < -20000) val |= SNES_UP_MASK;
    if (SDL_JoystickGetAxis(keyssnes, 1) > 20000) val |= SNES_DOWN_MASK;
    if (SDL_JoystickGetAxis(keyssnes, 0) < -20000) val |= SNES_LEFT_MASK;
    if (SDL_JoystickGetAxis(keyssnes, 0) > 20000) val |= SNES_RIGHT_MASK;
#else
    //player1
    if (keyssnes[sfc_key[L_1]] == SDL_PRESSED) val |= SNES_TL_MASK;
    if (keyssnes[sfc_key[R_1]] == SDL_PRESSED) val |= SNES_TR_MASK;
    if (keyssnes[sfc_key[X_1]] == SDL_PRESSED) val |= SNES_X_MASK;
    if (keyssnes[sfc_key[Y_1]] == SDL_PRESSED) val |= SNES_Y_MASK;
    if (keyssnes[sfc_key[B_1]] == SDL_PRESSED) val |= SNES_B_MASK;
    if (keyssnes[sfc_key[A_1]] == SDL_PRESSED) val |= SNES_A_MASK;
    if (keyssnes[sfc_key[START_1]] == SDL_PRESSED) val |= SNES_START_MASK;
    if (keyssnes[sfc_key[SELECT_1]] == SDL_PRESSED) val |= SNES_SELECT_MASK;
    if (keyssnes[sfc_key[UP_1]] == SDL_PRESSED) val |= SNES_UP_MASK;
    if (keyssnes[sfc_key[DOWN_1]] == SDL_PRESSED) val |= SNES_DOWN_MASK;
    if (keyssnes[sfc_key[LEFT_1]] == SDL_PRESSED) val |= SNES_LEFT_MASK;
    if (keyssnes[sfc_key[RIGHT_1]] == SDL_PRESSED) val |= SNES_RIGHT_MASK;
    //player2
    /*
    if (keyssnes[sfc_key[UP_2]] == SDL_PRESSED)		val |= SNES_UP_MASK;
    if (keyssnes[sfc_key[DOWN_2]] == SDL_PRESSED)	val |= SNES_DOWN_MASK;
    if (keyssnes[sfc_key[LEFT_2]] == SDL_PRESSED)	val |= SNES_LEFT_MASK;
    if (keyssnes[sfc_key[RIGHT_2]] == SDL_PRESSED)	val |= SNES_RIGHT_MASK;
    if (keyssnes[sfc_key[LU_2]] == SDL_PRESSED)	val |= SNES_LEFT_MASK | SNES_UP_MASK;
    if (keyssnes[sfc_key[LD_2]] == SDL_PRESSED)	val |= SNES_LEFT_MASK | SNES_DOWN_MASK;
    if (keyssnes[sfc_key[RU_2]] == SDL_PRESSED)	val |= SNES_RIGHT_MASK | SNES_UP_MASK;
    if (keyssnes[sfc_key[RD_2]] == SDL_PRESSED)	val |= SNES_RIGHT_MASK | SNES_DOWN_MASK;
     */
#endif

#ifdef NETPLAY_SUPPORT
    if (Settings.NetPlay)
        return (S9xNPGetJoypad(which1));
#endif

    return (val);
}
