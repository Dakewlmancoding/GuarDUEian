/************************************************** VARIABLES ***************************************************/

const int introNoteArray[] = {1695, 0000, 1581, 0000, 1583, 0000, 1690, 0000, 1582, 0000, 1688, 0000, 1581, 0000, 1693, 0000, 1581, 0000, 1690, 0000, 1583, 0000, 1695, 0000, 1582, 0000, 1690, 0000, 1684, 0000, 1688, 0000, 1581, 0000, 1693, 0000, 1583, 0000, 1582, 0000, 1684, 0000, 1695, 1352, 0000, 1583, 0000, 1688, 0000, 0000, 1583, 1471, 0000, 1690, 0000, 0000, 1684, 1469, 0000, 1688, 0000, 0000, 1684, 1462, 0000, 1693, 0000, 0000, 1684, 1464, 0000, 1690, 0000, 0000, 1684, 1574, 0000, 1695, 0000, 0000, 1583, 1469, 0000, 1688, 0000, 0000, 1583, 1471, 0000, 1691, 0000, 0000, 1583, 1581, 0000, 0000, 1693, 0000, 1583, 1471, 0000, 1690, 0000, 1583, 0000, 1695, 0000, 0000};

const float introTimingsArray[] = {0, 0.16061845625, 0.00067204375, 0.07997320625, 0.00067204375, 0.07997320625, 0.00067204375, 0.07997320625, 0.00067204375, 0.07997320625, 0.00067204375, 0.07997320625, 0.00067204375, 0.07997320625, 0.00067204375, 0.07997320625, 0.00067204375, 0.07997320625, 0.00067204375, 0.07997320625, 0.00067204375, 0.07997320625, 0, 0.07997320625, 0.00067204375, 0.07997320625, 0.00067204375, 0.07997320625, 0.00067204375, 0.07997320625, 0.00067204375, 0.07997320625, 0.00067204375, 0.07997320625, 0.00067204375, 0.07997320625, 0.00067204375, 0.07997320625, 0.00067204375, 0.07997320625, 0.00067204375, 0.07997320625, 0, 0, 0.07997320625, 0.00067204375, 0.07997320625, 0.00067204375, 0.07997320625, 0, 0.00067204375, 0, 0.07997320625, 0.00067204375, 0.07997320625, 0, 0.00067204375, 0, 0.07997320625, 0.00067204375, 0.07997320625, 0, 0.00067204375, 0, 0.07997320625, 0.00067204375, 0.07997320625, 0, 0.00067204375, 0, 0.07997320625, 0.00067204375, 0.07997320625, 0, 0.00067204375, 0, 0.07997320625, 0.00067204375, 0.07997320625, 0, 0.00067204375, 0, 0.07997320625, 0.00067204375, 0.07997320625, 0, 0.00067204375, 0, 0.07997320625, 0.00067204375, 0.07997320625, 0, 0.00067204375, 0, 0.07997320625, 0, 0.00067204375, 0.07997320625, 0.00067204375, 0, 0.07997320625, 0.00067204375, 0.07997320625, 0.00067204375, 0.07997320625, 0.00067204375, 0.16061845625, 0};

const int introLen = 108;

const int loopNoteArray[] = {1359, 0000, 1466, 0000, 1465, 1240, 0000, 1242, 0000, 0000, 1469, 1245, 0000, 0000, 1466, 0000, 1359, 0000, 1466, 1240, 0000, 0000, 1242, 0000, 1240, 0000, 1469, 1245, 0000, 0000, 1466, 0000, 1359, 0000, 1466, 0000, 1240, 0000, 1242, 0000, 1469, 1245, 0000, 0000, 1466, 0000, 1359, 0000, 1466, 1240, 0000, 0000, 1465, 1242, 0000, 1240, 0000, 0000, 1469, 1245, 0000, 0000, 1466, 0000};

const float loopTimingsArray[] = {0, 0.16061845625, 0.16196254375, 0.16061845625, 0.00067204375, 0, 0.07997320625, 0.00067204375, 0.07997320625, 0, 0.00067204375, 0, 0.16061845625, 0, 0.00067204375, 0.16061845625, 0.00067204375, 0.16061845625, 0.16196254375, 0, 0.16061845625, 0, 0.00067204375, 0.07997320625, 0.00067204375, 0.07997320625, 0.00067204375, 0, 0.16061845625, 0, 0.00067204375, 0.16061845625, 0.00067204375, 0.16061845625, 0.16196254375, 0.16061845625, 0.00067204375, 0.07997320625, 0.00067204375, 0.07997320625, 0.00067204375, 0, 0.16061845625, 0, 0.00067204375, 0.16061845625, 0.00067204375, 0.16061845625, 0.16196254375, 0, 0.16061845625, 0, 0.00067204375, 0, 0.07997320625, 0.00067204375, 0.07997320625, 0, 0.00067204375, 0, 0.16061845625, 0, 0.00067204375, 0.16061845625};

const int loopLen = 64;

const int slowFactor = 1;

/************************************************** FUNCTIONS ***************************************************/


bool doneIntro = false;
int songPos = 0;
float nextWait = 0;
unsigned long previousMillis = 0;


void updateSong(){
    unsigned long currentMillis = millis();
    /*
    Serial.print(currentMillis-previousMillis);
    Serial.print(" < ");
    Serial.println(nextWait);
    */

    if (currentMillis - previousMillis >= nextWait) {
        if (not (doneIntro)){
            if (songPos<introLen){
                if (introNoteArray[songPos] > 0){
                    Serial2.print(introNoteArray[songPos]);
                    Serial.println(introNoteArray[songPos]);
                }
                /*
                else{
                    Serial2.print("0000");
                }
                */
                
                
                nextWait = introTimingsArray[songPos] * 1000 * slowFactor;
                previousMillis = millis();
                while (not Serial2.available()){} //to not overload the UNO
                Serial2.flush();
                //Serial.print("SongPos =");
                //Serial.println(songPos);
                songPos++;
            }else{
                doneIntro = true;
                songPos = 0;
            }
        }else{
            if (songPos<loopLen){
                if (loopNoteArray[songPos] > 0){
                    Serial2.print(loopNoteArray[songPos]);
                    Serial.println(loopNoteArray[songPos]);
                }
                /*
                else{
                    Serial2.print("0000");
                }
                */
                nextWait = loopTimingsArray[songPos] * 1000 * slowFactor;
                previousMillis = millis();
                while (not Serial2.available()){} //to not overload the UNO
                Serial2.flush();
                //Serial.print("SongPos =");
                //Serial.println(songPos);
                songPos++;
            }else{
                songPos = 0;
            }
        }
    }
}

void resetSong(){
    doneIntro = false;
    songPos = 0;
    nextWait = 0;
}

void stopSong(){
    Serial2.print("0000");
}