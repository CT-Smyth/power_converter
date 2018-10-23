void disp_menu_move(int mnu){


    String disp;

    display.setContrast(255);
    
    display.clear();
    display.setFont(ArialMT_Plain_10);
    display.setTextAlignment(TEXT_ALIGN_CENTER);

  
    disp = modes[mnu+1];   
    display.setFont(ArialMT_Plain_10);
    display.drawString(64, 0, disp);

    disp = modes[mnu+2];   
    display.setFont(ArialMT_Plain_24);
    display.drawString(64, 18, disp);

    disp = modes[mnu+3];   
    display.setFont(ArialMT_Plain_10);
    display.drawString(64, 48, disp);
    
    display.display();

    dispTimeDue = timeNow + disp_delay;

  
}





void disp_menu(int mnu){

    String disp;

    display.setContrast(128);
    
    display.clear();
    display.setFont(ArialMT_Plain_10);
    display.setTextAlignment(TEXT_ALIGN_CENTER);
    disp = modes[mnu+2];   
    display.setFont(ArialMT_Plain_24);
    display.drawString(64, 18, disp);
  
    display.display();

    dispTimeDue = timeNow + disp_delay;

    sendMode(mnu);

  
}
