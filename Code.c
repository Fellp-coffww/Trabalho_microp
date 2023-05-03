#include <Adafruit_LiquidCrystal.h> 
#include <Keypad.h> 
//Inclui as bibliotecas para manipualção do teclado matricial e do display lcd 
int n = 0;			
Adafruit_LiquidCrystal lcd(0); //Seta a posição que o cursor inicializa 
const byte lin  = 4; //Define o número de linhas no teclado 
const byte col = 4; //Define o número de colunas no teclado 
byte ent_lin [4] = {3,4,5,6}; // Matriz contendo as entradas das linhas do teclado
byte ent_col [4] = {7,8,9,10}; // Matriz contendo as entradas das colunas do teclado 
String sen [4] = {}; //Matriz com a senha que será digitada pelo usuário 
String senha [4] = {"1","2","3","4"}; // Matriz com a senha correta 
bool est = 0; // Estado para senha, sendo 1 para correto e 0 para incorreto 
int f = 0; 
const char teclas [lin] [col] = {
  {'1','2','3','A'},
  {'4','5','6','B'}, 
  {'7','8','9','C'},
  {'*','0','#','D'}
}; // Cria um vetor com as teclas do teclado 

Keypad tec = Keypad(makeKeymap(teclas),ent_lin,ent_col,lin,col); //Configura o teclado com as teclas do teclado, n° de linhas e colunas e suas entradas

void setup() {

pinMode(11, OUTPUT); //Saida do motor Vcc
Serial.begin(2400);
lcd.begin(16,2); //Define o tamanho do display lcd 
lcd.print("Digite a senha: "); //Imprime a mensagem inical na tela pedindo a senha
 
}

void loop() {


String let = String(tec.getKey()); //Instrução para mostrar a tecla que o usuário pressionar em formato string 
  lcd.setCursor(0, 1); // Define irá mostrar as teclas do usuário  
  while (let == 0) // Intrução de repetição para requisitar um numero para o usuário 
    let = tec.getKey(); //Instrução para mostrar a tecla que o usuário pressionar em formato char 
  if (let){
    lcd.print(let); // Imprime na tela o número pressionado pelo usuário  
    sen[f] = (let);//Posiciona o número pressionado pelo usuário em uma matriz de senha 
    f = f+1;// Incrementa 1 na váriavel f 
  if (sen[0] ==senha[0] and sen[1] ==senha[1] and sen[2] ==senha[2] and sen[3] ==senha[3]){ //Verifica se a senha está correta 
     lcd.clear(); // Limpa a tela para imprimir nova mensagem 
     lcd.print("Senha correta!"); // Imprime a mensagem de senha correta 
     Serial.println(let); // Imprime no monitor serial o número digitado pelo usuário 
     est = 1; // Devolve o estado de 1 para o variavel est, mostrando que a mensagem está incorreta.  
	 delay(2000); //Delay de 2 segundos 
     lcd.clear(); // Limpa a tela para imprimir nova mensagem
     analogWrite(11,255);//Usa a saída Pwm para ligar o motor na potência maxima 
     lcd.print("Motor ligado"); // Imprime na tela que o motor está ligado 
    }
  if (f == 4 and est == 0){ //condicional para caso a senha esteja errada
    lcd.clear(); // Limpa a tela para imprimir nova mensagem
    lcd.print("Senha incorreta!"); // Imprime a mensagem de senha incorreta
    }
  }}
