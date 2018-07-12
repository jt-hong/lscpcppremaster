// LSCP.cpp: 定义控制台应用程序的入口点。
//

#include<iostream>
#include<string>
#include<exception>
#include<fstream>
#include<ostream>
#include<map>
#include<regex>
#include"FuncPort.h"
using namespace std;
class FileException : public exception             //Define File w/r Exception
{
public:
	const char * what() const throw()
	{
		return "File Open Exception";
	}
};

void ReadConfig(map<string, int> &conf);

int main()
{
	map<string, int> config;
	//ReadConfig(config);
	StrProcess  Process = StrProcess();
	std::string Path = "";  //File Path
	Process.ReadFile(Path);
	std::cout << Process.GetStr()<<endl;
	Process.IsCode(true);
	Process.BuildDict();
	Process.DoPunction();
	Process.DoIdentifiers();
	std::cout << Process.GetStr();
	return 0;
}

void ReadConfig(map<string, int> &conf)
{
	string Answer;
	string FileName = "config.ini";
	ifstream ConfigFile;
	string StrLine;
	string Key;
	int Value;
	try
	{
		//FILE *ConfigFile = fopen(FIleName,"r");
		ConfigFile.open(FileName.c_str());
		if (!ConfigFile.is_open())
		{
			throw FileException();
		}
	}
	catch (FileException &e)
	{
		std::cout << e.what() << ",Check config.ini pls or" << endl << "input yes to build a new File:" << endl;
		cin >> Answer;
		if (Answer == "yes")
		{
			cout << "Here will build a config.ini file:" << endl;
			fstream file(FileName.c_str(), fstream::out);
			ConfigFile.open(FileName.c_str());
		}
		else
		{
			exit(1);
		}
	}
	while (!ConfigFile.eof())
	{
		getline(ConfigFile, StrLine);
		size_t Pos = StrLine.find('=');
		Key = StrLine.substr(0, Pos);
		Value = atoi(StrLine.substr(Pos + 1).c_str());       //string to int
		conf.insert(pair<string, int>(Key, Value));
	}
	map<string, int>::iterator Check;
	Check = conf.begin();
	while (Check != conf.end())
	{
		cout << Check->first << endl;
		cout << Check->second << endl;
		Check++;
	}
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
// . . . . . . . . . . . . . . ' ? [ ? I .   . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
// . . . . . . . . . . . . . - n t | \ | | | \ . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
// . . . . . . . . . . ' | L u | \ | | ( 1 ( ( t ' . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
// . . . . . . ' . j n t / / | | ( { \ ) ) ( | ( . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
// . . . . . ' j X z J x t t \ ) ( { ( ( | | ( ( j . . . ' ' " . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
// . . . . . | x z u v u 0 O j / | | | \ x \ | | { . ` n / j r . . . . . . . . . . . . . . . ' . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
// . . . . ^ v m n x n x n u u v | | | | / / ( | / t f r j j j . . . . . . . . . ' ` f ( ) ) ( ( / t } . ` . . . . . . . . . . . . . . . . . . . . . . . . . . . .
// . . . . J z Q n r r x x r x x Y \ \ | | v / t c j r x r j j ^ . . . . . . . . j 1 1 1 1 { { 1 { 1 1 { 1 1   . . . . . . . . . . . . . . . . . . . . . . . . . .
// . . . ` u w w u r r x x x x x x J \ \ / r f c n C x x x r j x . . . . . . . + ) 1 ) ) 1 1 1 { { { { { { { { } , . . . . . . . . . . . . . . . . . . . . . . . .
// . . . U n w q u x r x x x Q L n u J U x n Q 0 U J L U z v Y X + ` . ` . . . \ ) ) ( | | ( ) ) 1 { { { { { { } } ] , . . . . . . . . . . . . . . . . . . . . . .
// . . ' X J q w u x x x x r x x n c O c U j / t | | | ( | | | ( ) ) ) ) | { l x ( r Y U J U X c f ( 1 { } { { } } [ } {   . . . . . . . . . . . . . . . . . . . .
// . + J X q p w C x r x x x x r c c f / \ ( ( ( ( | ( ( ( ( ( ( ( ( ) ) ) ) ) ( u U U U J L J J U X v \ 1 { { } } } { { } + . . . . . . . . . . . . . . . . . . .
// n n X c p q m 0 x r x r x J / \ \ | ( | ( ( | | \ t r u z X c u r f \ | | ( ( / | ( ) \ z J L Q J U Y c 1 { } } } } } { } f ' . . . . . . . . . . . . . . . . .
// x j j v q p m J n x n J f | ( ( ( ( ( | | t c J C C C L C C C C J C C C Y X \ ( ) ) 1 1 ) ) v U Z C J Y X \ { { { { } } } } / ` ' . . . . . . . . . . . . . . .
// f f j c q m Z Q u X j ( { ) { ( ) { / c L C 0 O 0 C C C L Q 0 0 J J J C z / c ) ) ) ) ) 1 ) ) | U C 0 J U Y u { { { } } [ } { )   ' . . . . . . . . . . . . . .
// f f f J c m Z m J t { 1 } | 1 { / X C Q O m 0 0 \ { [ } ] ] ] ] [ { } f / C | ) ) ) ) ) ) ) ) | ( v J O J J Y c { { } { } } } { { . ' . . . . . . . . . . . . .
// t f t j u Z U X f / | ( | \ / X Q 0 O Z Q n { ] ? - - ? _ _ _ _ - [ t \ ) t ( ) ) ) ) ) ) ) ) / X / r J Q J J U u { { { } } } { { { . . . . . . . . . . . . . .
// t f f v C Z n t t / \ | \ x C 0 Z w Q x ] - + ~ > l : ; ; ; ; I < r ) ) X ( ) ] 1 1 ) ) ) ) ) Y r u ( / Y C L J Y j ) { } { } { { { { ' . . . . . . . . . . . .
// j x C O m x f t t t x f v Q Q X 0 Y } - i ; ; : : , , , , , , : { \ - [ ( | 1 1 _ ) ) 1 ) ) ) 1 \ / / ( | Y L C J Y \ { { { { { t { { " . . . . . . . . . . . .
// z Z Z m j f t t f X j J Q Z z L \ ] ? 1 ) \ j r x x / < " : : ; \ v ; U | | { { ) 1 ) ~ ) ) ) ( j c / | ) ( Y C J U X ) { { { { { f { } ` . . . . . . . . . . .
// Z m q r j f t j U x Q Q r X C > I : : : , , , , : , : , \ j _ ] ) ; : ) | | ( 1 ) } ) [ 1 ) [ ( v t / j ) ) ( U Q U Y v ) { r ) 1 ) j ) I ' . . . . . . . . . .
// m w n j f f j J x C O ( f C ; : , , , , , , " " " " , , : : i n r : - ( ( | | | ) ( ) ) ) 1 [ ) f / ( / ) ) ) / Y 0 J U ( 1 ) v | ) 1 t ) ' . . . . . . . . . .
// m u j j f j C r L Q } I C I ; , , , , , , , " " " " " " , , ; | u ; / ( | | | | | | | | ( ) ) ) | \ | \ n ( ) ( r J Q J X 1 { ( c 1 ) 1 | ` . . . . . . . . . .
// X u f j f c n X Q ? l C < ; : , , , , , , , , , " " " " " , : f , f \ ( | | | | | | | | | ( ( ( \ \ x | t | ) ) ) Y O 0 Y | 1 ) J c ) ) X ' . . . . . . . . . .
// u j f j j c v 0 - ! ~ + I x I : : : : , " , " " , " " " " " I \ : l | | | | | | | | | | | | | | \ | / ( | \ ) ) ) ( U 0 O n ) 1 \ X j ) ( ` . . . . . . . . . .
// L x j j n n C ? I + U < i f o # # * o d j ~ I 1 , , " " , , ; ; : \ \ | | | \ \ | | | | | | | | | f ( | ( c ) ) ) ) x Q Q L ) ) 1 U X ) ( ( ' ' . . . . . . . .
// r x j x n X 1 ; ; l ) # & # # # o * # o * # W u > ( ^ , , , : , : n \ | | | | | | | ( | | | | | | j r | ) / ) ) ) ) ( U Q Z | 1 ) U U X ) \ ' ' . . . . . . . .
// x x x L v L ; : : L M M * j ] + + _ - ? ) J * # # f I : , , : : : t \ | \ \ \ \ | | \ \ | | | | \ f c | ( ) ( ) ) ) ) n O z \ ) ) v J U | | . . . . . . . . . .
// x x u u U I ; : r * W q ? ^ ^ ` ' ` ' ' , + ] x M # b i { : : ; , + x ( \ \ \ \ | | | | | | | | | f U | ( | ( ( ) ) ) ( Q X t ) 1 f 0 J n \ ' . . . . . . . . .
// x x u x } : ; ; l o w ; ` ^ , c . . . . j q l _ { * M * ! { , , , , ; : ( \ \ \ | | | | | | | | / f / | ) \ \ ( ) ( ) ( U v f ( ) u v J Y / ' . . . . . . . . .
// x n Y n ; : ; ; l b : ` ` f * Q ' . . . < M # > ~ { # # n > : , , " , , , : I \ | | | | | | | | / r x | | / \ | ) ( ) ) f f \ ( ( f / C J v . . . . . . . . . .
// x X r } : : : : : - ` ` ; o b ) l ` ' ' ' X # o : + } M Q : , , " " , , , , , , > \ | | \ | | \ n c J \ | | \ | ( ( ) 1 ) \ \ ) t ( | Q J C . . . . . . . . . .
// n i r ; ; : : : : " ` ` z M t { f C J j ? t p M u " > a ? , , , , " , , " " " , , ; 1 ( \ | | / U Q c \ ( \ \ | ( ( ) { } | ( ( | ( | 0 C z ' . . . . . . . . .
// c + j ; ; : : : : , ^ ` c h ) 1 c M # # L J Q M p ^ : a p : , , , , , , , , " , , " " ; f | | / n c u | | / | ( ( ( ) 1 1 X \ t ) ) / 0 m I . . . . . . . . . .
// v ? c I : : : : : : , " ; a / | v # M # U z n M X ^ " 1 ; , , , , " , , , , , , , , , , : < | / { j j | | j \ ( ( ( ) ( ( z ( ( ) ) t U C ' . . . . . . . . . .
// + - - ; ; ; : : : : : , - b p c j C Q v ^ > c # ^ " " , ; " , , " " , , , , , , , , " " , " , r ! | f | \ f \ ( ( ( ( ) | / ( ) ) ( n c f ~ . . . . . . . . . .
// l - ! ; ; ; I l l I ; ; ; I ; ~ 0 b Q j i l o ] " " " , , , , " " , , , " " , , , , ^ " " " , : , \ | | \ C f | | | ) ) | u | ( ) ) n | ( | . . . . . . . . . .
// l ! l I ; ! i i i i ! l ; : : : I : - b h w ; , " , , , , , , " , , , , , " , , , , " , , , , , " ; \ ( ( i \ | | | ( | | x / \ ( ) ( ) ) ( " . . . . . . . . .
// I l l I l i i i i i ! ! l ; : : , : : ; ! I : , , , , , , , , , , , , , , , , , , , , , , , , , , , , } { , \ | | | | | | / f r | ( ( ) ) ( J ' . . . . . . . .
// l ; > I l i i i i i i i ! l ; : , : , , , , , , , , , , , , , , , , , , , , , , , , , , , , , , " " , , : [ | | | | | | ( \ j J ( ( ) ) ) ) / ^ . . . . . . . .
// l I \ I l i i i i i i i i ! l : , : , , : , , , , , , , , , , " " " , , , , , , , , , , , I ; , " " " , , : \ | | | | | ( / r U \ ( ) ) ) ) (   . . . . . . . .
// I ; ; I I ! i i i i i i i i l : : : : : : : " , , , , , , , , " " , , , , " , , , , " " ; I : ; [ " " " , , : | | | | ( | f j C \ ( ] ) ) ) | ? . . . . . . . .
// l ; ; I I l ! ! ! ! i i i i l : : : : : : : : : , , , , , , , , , , , , , , , , , , , " I t < l ; ; l " , , : l \ | | | | j n C j ) ] ) ) ) ( Q . . . . . . . .
// ! I ; ; ; I l l ! ! i i i ! l ; ; : : : : : : : , , , , , , , , , , , , , , , , , , - v Q a M M m > l } : , , , I ( | | | x z Q x ( ] ) ( ( ) v . . . . . . . .
// ! I ; ; I I ; I ; I l l l I ; : ; : : : : : : : : : , " " , , , " , , , , , , , , , ! j \ i [ h o * X l { " , , , t | | | u U C n ) ] } ( ) ( f . . . . . . . .
// - I ; ; ; ; ; ; I ; ; ; ; ; ; : ; ; ; : : : : : : : , " , , , , " " , , , " " , , " , , , : ! + [ k o W ! " , , , , t | | _ [ J x ( } } ) ( ( f . . . . . . . .
// z l I ; ; ; ; ; ; ; ; ; ; ; ; : : ; ; : : : : : : : , " , : ! : , , , , , " , , , , " " ` ' ' ' ^ + n * M : , , , , : | / r ! J j ( { ) ( ( ) f . . . . . . . .
// n ! I ; ; ; ; ; ; ; ; : ; ; ; ; ; ; : : : ; ; : : : : : : ? - : : , , , , , , , , , " " _ j ' . ' ' ; r # * I , , , , ) f X i J t ( ( ( ) ( ( / . . . . . . . .
// n ! I ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; : : ; : : ; : : : : : ! : : : , , , , , , , , , " Y b ] ' . . ' ' ! U # p ; , , , , ! t _ J t ( ( ) { ( ( / . . . . . . . .
// + v I I I I ; ; ; ; ; ; ; ; ; ; ; ; ; ; : : : : ; ; ; : : ; : : : , , , , , , , , , : a f ? . . . ' Q I _ o # 1 , , , , l ; r L t | ( ) [ ) | / . . . . . . . .
// i ? ! l I I ; ; ; ; ; ; ; ; ; ; ; ; ; ; : : : : : ; ; : : : : : : , , , , " , , , , L z ) ) j } ' . X b ; \ M M " , , , : : Q U / | | ( } ) ( t ' . . . . . . .
// ! i | l l I I l I I I I l I ; I I I ; ; ; ; ; ; : : ; ; ; : : : : : : : : : , , , : h f ) t 0 J 1 ` ( a v + M # > : , , , : L v \ ( | | 1 ( | / ' . . . . . . .
// l ! ! l l ; l l I I I I I I I ! j L Q j l ; ; ; : : ; : ; ; : : : : : : : , : : : : b j | J M # m c z Z a " J M C : , : , ; U t / | | | | ( | t . . . . . . . .
// l l l l l l l l I I l l I l i q q p d q I ^ l < : ; : : : ; : : : : : : : : : : , ; O p / Q M W W Q v Q a " ( M # - ! { : ] C t t / \ \ | | \ n . . . . . . . .
// l l l l l l l l I I l l l + p p p p p p w , " ^ ` < : ; ; ; : : ; ; : : : : : : , , ; / w n h M W C n Y a " } W # l ; ; : J v f L / \ \ ) | / X . . . . . . . .
// ! ! l l l l l I l l l ! ~ q p d d d d d p Z : ^ ' ^ + ; ; ; ; ; ; ; ; ; : : : : : : : : ? b n c / _ 1 r k " ? W o I : : " U f f X t / \ ] | r } . . . . . . . .
// ! ! l l l l l l l l l < w p d p p p d d p p w 0 : ^ ^ I I ; : : ; ; : : ; ; : : : : : : ; < h x ? ` { w Q ^ - M M { : : ) Y j C n t / \ ( t Y   . . . . . . . .
// i ! ! l l l l l l ! > q w q q w q p p p q p d d q O > ; ! > ; : : : : : ; ; ; ; : : : : : ; i a v - m k , ^ { W M } Y l U n n 0 x t / { \ t n . . . . . . . . .
// i i i i ! ! l l l ! - 0 t / / | \ \ \ \ v b p d p d p m w O ! I : : : : ; ; ; ; : : ; ; : : ; < o o m ' ` ' ( W k ; ; ( J r m L f t / \ | j x ' . . . . . . . .
// i i i i i i ! ! l ! n \ ( ( ( ( ( ( ( ( ( | u p p p d d d p ) ; ; ; ; ; : : : : ; I l l l I ; I i U " ` ` , X * c : l U x Q Z c f / / { t Y ' ' . . . . . . . .
// i i i i i i i ! i ! | ( 1 ) ( ( ( ( ( ) ) ( | \ p q d d p p q > ; ; ; ; : : : ; I ! i i i ! I ; ; l , " ` z ? I ; I C X X Z 0 r f t t t j u . ' . . . . . . . .
// i i i i i i i i i < ( ) ) ( ( ( ( ( ( ( ( ( ) ( \ p q p d d q ) I ; ; ; ; ; ; ; I ! ! i i ! ! l I : : : : : : ; I ( J m / Z Y j f t ) t n x . . . . . . . . . .
// > > i i i i i i i - \ ) ( ( ( ( ( ( ( ( ( ( ) ) ( \ p p p d q ! ; : ; ; ; ; ; ; l i i i i i ! ! l : : ; : : : : ~ C z \ Z O r j f f \ j X ' . . . . . . . . . .
// > > i i i i i i i ? | ( ( ( ( ( ( ( ( ( ( ( ( ( ( ( u q d d Z l I ; ; ; ; ; ; ; l i i i > > i i ! I : : ; : : ~ J ~ ( Y 0 u r j j f / c J . . . . . . . . . . .
// > i i i i i i i i + ( ) ( ( ( ( ( ( ( ( ( ( ( ( ( ( | q p p 1 l I ; ; ; ; ; ; ; I i i i i i i i i l : ; : I [ f l i | O U x r j j | j Y x ' . . . . . . . . . .
// > > > > > > i i i < ( ) ( ( ( ( ( ( ( ( ( ( ( ( ( ( ( Q p w > l ; l ; ; ; ; ; ; ; l ! i i i i i i l ; ; , [ ; ; ; | 0 Q n x j r j x J X v . . . . . . . . . . .
// > > > > i > i i > > \ ( ( ( ( ( ( ( ( ( ( ( ( ( ( ( ( v p L l l ; l ; ; I l ; ; ; I l ! i i i i i I ; ; : ; ; ; { Z O n x x x r x x Y J v . . . . . . . . . . .
// ? ~ < > > > > > i > ] ) ) ) ( ( ( ( ( ( ( ( ( ) ( ( ( j Z _ l I l I I I I I I I ; ; I I l ! ! i l I ; ; ; ; I > Z m v x r x x x n X u U { ' . . . . . . . . . .
// / ~ > > > > > > i > > v ( ) ( ( ( ( ( ( ( ( ( ( ( ( ) f t ! I I l l I I I I I I ; ; ; ; l ; ; I I ; ; ; ; ; l O Z z n x x x x v Z u u X ' ' . . . . . . . . . .
// t ( ~ > < < < < > > > > ) ( ( ( ( ( ( ( ( ( ( ( ) ) ( v < ! l I l l I I I I I I I I I I ; ; ; ; ; ; ; ; I ] Z m z u x x n u v Z Q u u u ` ' . . . . . . . . . .
// f t ? ~ < < < < < < > < ~ 1 ( ( ( ( ( ( ( ( ( ( ) ( x i ! ! l l I I I I I I I I I I I I ; ; ; ; ; ; I > C 0 m v n n n n u v w 0 v u v j . . . . . . . . . . . .

