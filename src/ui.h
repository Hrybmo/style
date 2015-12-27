
void ui_init(void);
void ui_destroy(void);
void ui_whtBackgroud(void);
void ui_blkBackgroud(void);
void ui_pushStack(void);
void ui_popStack(void);
  
//buff below must be static
void ui_setTempTo(char *buff);
void ui_setHiTempTo(char *buff);
void ui_setLoTempTo(char *buff);
void ui_setDayTo(char *buff);
void ui_setDateTo(char *buff);
void ui_setTimeTo(char *buff);
void ui_setBattTo(char *buff);