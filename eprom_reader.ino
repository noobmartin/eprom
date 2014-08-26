/*
 * This code reads the data in a 27C256 EPROM.
 * The chip can hold 32K 8-bit words, i.e 32KB or 256000 bits.
 *
 * The A0-A14 on the chip are address inputs.
 * The O0-O7 are data outputs.
 */

#define ADDRESS_BITS 15
#define DATA_BITS 8
#define MAX_ADDRESS 32768

int chip_enable = 9;
int output_enable = 8;

int address[ADDRESS_BITS] = {22,23,24,25,26,27,28,29,30,31,32,33,34,35,36};
int data[DATA_BITS] = {A0, A1, A2, A3, A4, A5, A6, A7};

void setup(){
  Serial.begin(115200);
 
  pinMode(chip_enable, OUTPUT);
  pinMode(output_enable, OUTPUT);
  
  int i;
  for(i = 0; i < ADDRESS_BITS; i++){
    pinMode(address[i], OUTPUT); 
  }
  
  for(i = 0; i < DATA_BITS; i++){
    pinMode(data[i], INPUT);
  }
  
  delay(5000);
  Serial.flush();
}

int run_once = 0;

void loop(){
  if(run_once == 0){
    unsigned long current_address = 0;
    for(current_address = 0; current_address < MAX_ADDRESS; current_address++){
      set_address(current_address);
      //delay(1);
      digitalWrite(chip_enable, LOW);  
      //delay(1);
      digitalWrite(output_enable, LOW);
      //delay(1);
  
      byte byte_data = read_byte();
  
      digitalWrite(output_enable, HIGH);
      //delay(1);
      digitalWrite(chip_enable, HIGH);
      //delay(1);

      Serial.write(byte_data);

      //Serial.print("Addr: 0x");
      //Serial.print(current_address, HEX);
      //Serial.print(" Data: 0x");
      //Serial.print(byte_data);
      //Serial.println();
  
    }
    run_once = 1;
  }
}

void set_address(unsigned long select_address){
  // Set the bits in the address array.
  digitalWrite(address[0], select_address&1 ? HIGH : LOW);
  digitalWrite(address[1], select_address&2 ? HIGH : LOW);
  digitalWrite(address[2], select_address&4 ? HIGH : LOW);
  digitalWrite(address[3], select_address&8 ? HIGH : LOW);
  digitalWrite(address[4], select_address&16 ? HIGH : LOW);
  digitalWrite(address[5], select_address&32 ? HIGH : LOW);
  digitalWrite(address[6], select_address&64 ? HIGH : LOW);
  digitalWrite(address[7], select_address&128 ? HIGH : LOW);
  digitalWrite(address[8], select_address&256 ? HIGH : LOW);
  digitalWrite(address[9], select_address&512 ? HIGH : LOW);
  digitalWrite(address[10], select_address&1024 ? HIGH : LOW);
  digitalWrite(address[11], select_address&2048 ? HIGH : LOW);
  digitalWrite(address[12], select_address&4096 ? HIGH : LOW);
  digitalWrite(address[13], select_address&8192 ? HIGH : LOW);
  digitalWrite(address[14], select_address&16384 ? HIGH : LOW);
}

byte read_byte(){
  byte new_byte = 0;
  
  int i;
  int j = 1;
  for(i = 0; i < DATA_BITS; i++){
    if(digitalRead(data[i]) == HIGH){
      new_byte = new_byte + j; 
    }
    j = j*2; 
  }
  
  return new_byte;
}
