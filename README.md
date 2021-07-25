# PoetReader

Dieses Projekt kann die Dichterliste nicht nur vom Dateisystem, sondern auch vom Web-Server direkt einlesen.

Das Projekt verwendet den Standard System-Socket, für Windows WinSock2 und für Unixuide Systeme den Unix-Socket.

In der Klasse SocketWebReader, wird die Datei "dichterliste.txt" über den Socket vom Web-Server eingelesen und als STD Stream zurückgegeben.

In der PoetReader Klasse, werden die gelesenen Daten verarbeitet. Da wir den C++ Standerd verwenden, kann die Klasse einmal einen FileStream oder den StringStream des SocketWebReaders verwenden.

# Verwenden der SocketWebReader Klasse
Zum Verwenden der Klasse, muss die Header-Datei über einen #include eingebunden werden, danach kann direkt eine neue Instanz erstellt werden.
Der Konstruktor hat folgende Argumente:
* Die IPv4 Adresse des Zielcomputers in der "dotted decimal notation" (xxx.xxx.xxx.xxx)
* Die Port-Nummer als const char* 
* OPTIONAL: einen Pointer um Fehler-Codes auszuwerten.

# Beispielaufbau
    SocketWebReader* socketWebReader = new SocketWebReader("172.20.4.30", "80");
    std::iostream* datei = socketWebReader->GetStream("GET /Quellen/fi/dichter_liste.txt\r\n");
    
# Beispielaufbau mit Error
    int fehler;
    SocketWebReader* socketWebReader = new SocketWebReader("172.20.4.30", "80", &fehler);
    std::iostream* datei = socketWebReader->GetStream("GET /Quellen/fi/dichter_liste.txt\r\n");

# Fehlermeldungen
Der SocketWebReader hat unterschiedliche Fehler-Codes

**Fehler-Codes im Konstruktor**
Fehler im Konstruktor können über den int* "error" ausgelesen werden, dieser Parameter ist Optional
* 0 Es ist kein Fehler abgetreten
* 1 Es konnte kein Socket erstellt werden.
* 2 Es wurde eine ungültige IP-Addresse übergeben, der SocketWebReader nimmt aktuell nur IPv4 Adressen im Format "dotted decimal notation" an, es wird auch keine Namensauflösung vorgenommen.
* 3 Der Socket, konnte nicht verbunden werden, möglicher weiße falsche Adresse oder falscher Port.

**Fehler-Codes bei GetStream**
* GetStream hat direkt keine Fehler-Codes, wenn die anfrage nicht gesendet werden kann, sollte man schauen, ob der Konstruktor einen Fehler hat.
* Fehlermeldungen auf Serverseite, oder bei der Request können über den Rückgabewert ausgelesen werden.
