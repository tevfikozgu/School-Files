Program ilk olarak text dosyas�n� okuyor ve e�er ba�ka "argument" girilmezse b�t�n dilin modelini ��kar�yor.
E�er di�er iki argument de girilirse ilk k�sm� atlay�p sadece dil modelindeki olas�l��� hesapl�yor.
Bunun i�in �nce text dosyas�n� g�venli bir okuma i�in ch ad�nda bir Array'e y�kl�yor. Daha sonra okunan bu text dosyas�ndaki
b�t�n harfler convert() fonksiyonu arac�l���yla "Lowercase" d�n���m� yap�yor. Bu tamamland�ktan sonra create() fonksiyonu devreye
girip ch arrayine kaydetti�imiz text dosyas�ndaki harfleri yine create() fonksiyonun i�inde yaz�lm�� algoritmayla
tek tek "Vocab LinkedList"i olu�turmaya ba�l�yor. Bunu bir ba�ka fonksiyon push() yard�m�yla yap�yor. Push() fonksiyonu
s�radaki harfin LinkedListte hangi noktaya yerle�tirilece�ine karar verip o naktaya yerle�tirmeyi yap�yor bu sayede
alfabetik s�ra olu�turulmu� oluyor. "Vocab LinkedList" olu�turulduktan sonra "occur_node"lar� olu�turmak i�in add_occurence() fonksiyonu i�leme al�n�yor.
Bu fonksiyon belirli bir harften sonra gelen harflerin ve bunlar�n miktarlar�n�n depoland��� linkedListi olu�turuyor. Fakat bunlar� ekrana output verirken hep tam ortadaki
eleman sorun ��kard��� i�in ve ekranda her zaman ger�ek sonu�tan bir eksik sayi verdi�i i�in g�venli bir sonu� ve kolay bir alfabetik s�ra olu�turup output vermek i�in Print()
fonksiyonu kullan�ld�. Bu fonskiyon dil modelini alfabetik ve eksiksiz bir �ekilde ekrana veriyor. Bir di�er yaz�lm�� olan PrintList() fonksiyonu ise sadece LinkedListin kotrol�
i�in yaz�lm�� olup LinkedListi ekrana veriyor. get_occurence() fonksiyonu vocab LinkedListeki herhangi bir �yenin text dosyas�ndaki toplam say�s�n� hesapl�yor. get_union_occurence()
fonksiyonu ise dil modelindeki bir harften sonra gelen bir ba�ka belirli harfin toplam say�s�n� hesapl�yor. calculateProbability() fonksiyonu ise nihai fonksiyon. get_union_occurence() ve
get_occurence() fonksiyonlar�n� harmanlay�p dil modelindeki bir harf i�birli�inin olas�l���n� hesapl�yor ve double veri tipi olarak d�n�� yap�yor.

**// Not: add_occurence() ve create() fonksiyonlar�ndaki array "Arr" eleman�n daha �nceden kaydedilip edilmedi�ini kontrol ediyor. Ba�ta arrayin b�t�n elemanlar�n� 0layarak her g�rd��� eleman�n
kar��l��� olan b�l�m� 1'leyerek ben bunu daha �nce g�rd�m (1) ya da g�rmedim (0) diyor. �rnek olarak 'h' harfinin arraydeki b�l�m� array[int('h')] == 0, bir kere g�r�ld�kten sonra  array[int('h')] == 1,
oluyor ve art�k bir daha noda eklenmesine gerek kalm�yor. Bu gayet verimli bir algoritma ve comlexityi azaltmay� sa�l�yor.

**// program�n zay�f noktas� ise Print() fonksiyonu, ortalama(average) ve worst case complexity o(n^3). Bu hi� istedi�imiz bir complexity de�eri de�il fakat �ok b�y�k input dosyalar� olmad��� i�in
daha g�venli bir yol olmas� dolay�s�yla bu fonksiyon bu �ekilde b�rak�ld�.

<< Te�ekk�r ederim >>
         </>
