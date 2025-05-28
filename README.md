#Philoshoper Probleminin Özü : Eşzamanlılık ve Senkronizasyon
- Philosopher problemi, eşzamanlı programlama dünyasındaki en temel zorluklardan birini somutlaştırır:birden fazla bağımsız işlemin veya thread'in paylaşılan kaynaklara(bu durumda çubuklar) aynı anda erişmeye çalışırken nasıl bir uyum içinde çalışması gerektiğini.Bu basitçe bir race condition'dan çok daha fazlası deadlock ve starvation gibi karmaşık sorunları ortaya çıkarır.
- Thread (İş parçacığı) Kavramı ve süreçlerden farkı
- -SÜreç (Process) işletim sistemi tarafından yönetilen bağımsız  bir program yürütme birimidir.Kendi bellek alanına, dosya tanımlayıcılarına ve kaynaklarına sahiptir.Süreçler arası iletişim IPC karmaşıktır
  - Thread ( İş Parçacığı) Bir sürecin içindeki daha küçük bir yürütme birimidir.Aynı sürecin bellek alanını, açık dosyalarını ve diğer kaynaklarını paylaşır.Bu, thread'ler arası iletişimi ve veri paylaşımını çok daha kolay hale getirir, ancak aynı zamanda senkronizasyon sorunlarına da yol açar.Philosopher projesinde her fizolozof bir thread olarak temsil edilecektir.
  - Neden Thread : Philosopher'lar aynı anda (eş zamanlı olarka) düşünebilir veya yemek yiyebilirler.Her bir filozofun bağımsız bir şekilde kendi yaşam döngüsünü sürdürmesi için thread'ler ideal bir model sunar.
# Race Condition
- Tanım : birden fazla thread'in aynı anda paylaşılan bir kaynağa (bellek alanı, değişken) erişmeye ve bu kaynağı değiştirmeye çalıştığı durumdur.İşlemlerin kesin yürütme sırası belirsiz olduğundan,sonucun tahmin edilemez veya yanlış olmasıyla sonuçlanabilir.
- Örnek : iki filozof anı anda bir çubuğu almaya çalışırsa ve bu işlem senkronize edilmezse, her ikisi de çubuğu başarıyla aldığını düşünebilir ve bu durum mantık hatalarına yol açar.
- Nasıl Çözülür:Senkronizasyon mekanizmaları (mutex'ler,semaphorlar) kullanarak kritik bölgelere erişimi kısıtlamak.
# Pthreads Kütüphanesi ve Senkronizasyon Mekanizmaları
- Pthreads,Unix benzeri sistemlerde thread tabanlı programlama için standart bir API'dir Philoshoper projesinde ana aracınız olacaktır.
- Thread oluşturma ve yönetimi
- pthread_create(pthread_t *thread, const_pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);
- thread: yeni oluşturulan thread in kimliği bu değişkene yazılır.
- attr:Thread'in nitelikleri (stack boyutu,ayrılma durumu vb ) genellikle NULL verilir varsayılan nitelikler için.
- start_routine : Yeni thread'in yürüteceği fonksiyonunun işaretçisi.BU fonksiyon void* döndürmeli ve void* argüman almalıdır.
- arg: start_routine fonksiyonuna iletilecek argüman.Tek bir void * olduğu için birden fazla veri gönderecekseniz bir struct oluşturup işaretçisini göndermelisiniz.
- pthread_join(pthread_t thread, void **retval); belirtilen thread'in tamamlanmasını bekler , retval: Thread'in start_routine fonksiyonundan döndürdüğü değeri almak için kullanılır.Genellikle NULL verilir.
- Önem: Eğer pthread_join kullanılmazsa, ana program thread'ler işini bitirmeden sonlanabilir ve bu da bellek sızıntılarına (zombi thread'ler) veya beklenmedik davranışlara yol açabilir.
- pthread_detach(pthread_t thread)
