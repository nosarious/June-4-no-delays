/*
 * a routine for the choreographer to send the total number of suitcases to everyone.
 */
void sendTotal(){
  /* 
   *  message will be 01update(xx) where xx is the new total of suitcases
   */
   sendMessage(01,"update",sTotal);
   /*
    * suitcase stotal will automatically set it's nextNumber to 01
    */
}
