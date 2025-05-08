# ft_ping

`ft_ping` est une réimplémentation simplifiée de la commande Unix `ping`, développée dans le cadre d'un projet d'apprentissage des réseaux bas-niveau et de la manipulation des sockets en C sous Linux.

## 🧠 Concepts clés

- Sockets RAW (SOCK_RAW)
- Protocoles ICMP et IP
- Calcul de checksum
- Structure `timeval` et gestion des timestamps
- Gestion des signaux (interruption avec `Ctrl+C` + `Ctrl+\`)
- Structures réseaux (`ip`, `icmp`, `sockaddr_in`, ...)
