Program ilk olarak text dosyasýný okuyor ve eðer baþka "argument" girilmezse bütün dilin modelini çýkarýyor.
Eðer diðer iki argument de girilirse ilk kýsmý atlayýp sadece dil modelindeki olasýlýðý hesaplýyor.
Bunun için önce text dosyasýný güvenli bir okuma için ch adýnda bir Array'e yüklüyor. Daha sonra okunan bu text dosyasýndaki
bütün harfler convert() fonksiyonu aracýlýðýyla "Lowercase" dönüþümü yapýyor. Bu tamamlandýktan sonra create() fonksiyonu devreye
girip ch arrayine kaydettiðimiz text dosyasýndaki harfleri yine create() fonksiyonun içinde yazýlmýþ algoritmayla
tek tek "Vocab LinkedList"i oluþturmaya baþlýyor. Bunu bir baþka fonksiyon push() yardýmýyla yapýyor. Push() fonksiyonu
sýradaki harfin LinkedListte hangi noktaya yerleþtirileceðine karar verip o naktaya yerleþtirmeyi yapýyor bu sayede
alfabetik sýra oluþturulmuþ oluyor. "Vocab LinkedList" oluþturulduktan sonra "occur_node"larý oluþturmak için add_occurence() fonksiyonu iþleme alýnýyor.
Bu fonksiyon belirli bir harften sonra gelen harflerin ve bunlarýn miktarlarýnýn depolandýðý linkedListi oluþturuyor. Fakat bunlarý ekrana output verirken hep tam ortadaki
eleman sorun çýkardýðý için ve ekranda her zaman gerçek sonuçtan bir eksik sayi verdiði için güvenli bir sonuç ve kolay bir alfabetik sýra oluþturup output vermek için Print()
fonksiyonu kullanýldý. Bu fonskiyon dil modelini alfabetik ve eksiksiz bir þekilde ekrana veriyor. Bir diðer yazýlmýþ olan PrintList() fonksiyonu ise sadece LinkedListin kotrolü
için yazýlmýþ olup LinkedListi ekrana veriyor. get_occurence() fonksiyonu vocab LinkedListeki herhangi bir üyenin text dosyasýndaki toplam sayýsýný hesaplýyor. get_union_occurence()
fonksiyonu ise dil modelindeki bir harften sonra gelen bir baþka belirli harfin toplam sayýsýný hesaplýyor. calculateProbability() fonksiyonu ise nihai fonksiyon. get_union_occurence() ve
get_occurence() fonksiyonlarýný harmanlayýp dil modelindeki bir harf iþbirliðinin olasýlýðýný hesaplýyor ve double veri tipi olarak dönüþ yapýyor.

**// Not: add_occurence() ve create() fonksiyonlarýndaki array "Arr" elemanýn daha önceden kaydedilip edilmediðini kontrol ediyor. Baþta arrayin bütün elemanlarýný 0layarak her gördüðü elemanýn
karþýlýðý olan bölümü 1'leyerek ben bunu daha önce gördüm (1) ya da görmedim (0) diyor. Örnek olarak 'h' harfinin arraydeki bölümü array[int('h')] == 0, bir kere görüldükten sonra  array[int('h')] == 1,
oluyor ve artýk bir daha noda eklenmesine gerek kalmýyor. Bu gayet verimli bir algoritma ve comlexityi azaltmayý saðlýyor.

**// programýn zayýf noktasý ise Print() fonksiyonu, ortalama(average) ve worst case complexity o(n^3). Bu hiç istediðimiz bir complexity deðeri deðil fakat çok büyük input dosyalarý olmadýðý için
daha güvenli bir yol olmasý dolayýsýyla bu fonksiyon bu þekilde býrakýldý.

<< Teþekkür ederim >>
         </>
