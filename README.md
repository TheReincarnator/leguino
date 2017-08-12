# Disclaimer / Warnhinweis

The instructions, images, schematics, source codes, etc. may not be accurate nor complete.
Use at your own risk.

LEGO® is a trademark of the LEGO Group of companies which does not sponsor, authorize or endorse this site.

Die Anleitungen, Bilder, Schematiken, Quellcodes etc. sind ggf. nicht akkurat oder nicht vollständig.
Verwendung auf eigene Gefahr.

LEGO® ist ein Markenzeichen der LEGO Group, die weder diese Website sponsort, noch autorisiert oder unterstützt.

# Einleitung

LEGO® Mindstorms ist eine wunderbare Plattform, um sich spielerisch der Robotik und Programmierung zu nähern. Kinder können ihre vorhandene LEGO®-Sammlung um Motoren und Sensoren ergänzen, und die grafische Programmier-Umgebung ist auf der einen Seite leicht zu verstehen, auf der anderen Seite enthält es bereits Konzepte wie Befehle, Schleifen, Verzweigung, Variablen und Ereignisse.

LEGO® Mindstorms ist jedoch (vor allem für den wissbegierigen Nachwuchs) nicht ganz günstig. Mein Sohn hatte zwar mittlerweile bereits eine schöne Sammlung LEGO®-Technic-Modelle mit Motoren, Lichtern und Schaltern, aber ohne Sensoren oder gar Programmierung.

Aber er hatte Interesse daran.

Also dachte ich mir: Versuchen wir mal die Lücke zu schließen und eine Open-Source-Plattform zu gründen, die auf LEGO®-Technic basiert, kostengünstig ist (Ziel <100€) und leicht verständlich. Hierfür schien Arduino bestens geeignet, aus folgenden Gründen:

* Ein Arduino Nano kostet unter 20€, teilweise sogar unter 10€
* Er lässt sich mit der LEGO®-Technic-Batterie betreiben
* Er startet (im Gegensatz z.B. zum Raspberry Pi) in unter einer Sekunde, ein Umstand, der in Modellen mit einschaltbarer Batterie wichtig ist
* Er hat genug Ein-/Ausgänge für ca. 10 Geräte

Die Programmierung erfolgt in C, was nicht so intuitiv ist, was man aber mit einer eigenen grafischen IDE (oder zumindest einer besseren API) kompensieren kann.

# Mehr über das Projekt lesen

Wenn du zunächst mehr über diese Projekt lesen möchtest, besuche bitte [meine Website](http://www.thomasjacob.de/kreativ/leguino/).

Wenn du dann auch deinen eigenen Leguino-Brick bauen möchtest, findest du in "docs" und "examples" alle Ressourcen, die dir dabei helfen sollten.
