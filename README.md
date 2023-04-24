# LEC009002 - Détecteur IR
Fichiers sources pour le produit LEC009002

## Description du produit

- Distance de détection réglable jusqu’à 10 cm
- Fonctionne même à la lumière du jour!
- Temporisation à la désactivation pour éviter des réactivations intempestives.
- 2 modes de fonctionnements :

1. **Mode direct (1 capteur)** le relais est commuté lorsqu’un objet se trouve en face du capteur. Le relais est relâché lorsqu’il n’y a plus d’obstacles devant le capteur.
2. **Mode bistable (2 capteurs)** Le relais est relâché lorsqu’un objet passe devant le second capteur.

## Utiliser les fichiers sources pour fabriquer le produit

Grâce aux fichiers sources publiés ici, vous pouvez être en mesure de faire fabriquer ce produit par un sous traitant.

**ATTENTION** ce produit est un **produit complexe à fabriquer** et nécessite notamment une programmation afin de pouvoir fonctionner. Vous devez pour cela posséder le programmateur et programmer vous même la carte. Cette étape peut nécessiter des connaissances techniques, si nécessaire, nous vous encourrageons à vous rapprocher d'un club.

**Remarque** ce produit est composé d'une carte mère, de 2 nappes de cable IDC 6 pin, et de 2 capteurs. Ce dossier permet uniquement de faire fabriquer la carte mère et les capteurs, vous devrez vous fournir les autres composants sur un site de revente (amazon, aliexpress, mouser, ...).

**Remarque 2** vous avez le choix entre 1 capteur coudé ou 1 capteur classique. Notez cependant que pour le capteur classique, le sous traitant JLCPCB n'est pas capable de souder le capteur sur le côté du PCB, vous devrez donc opter pour le capteur coudé si vous ne souhaitez pas souder vous même.

### Faire fabriquer chez un sous traitant

Il est aujourd'hui possible de faire fabriquer à moindre cout des cartes électroniques. Nous recommendons [JLCPCB](https://jlcpcb.com/) si vous voulez aller au moins cher. Si vous préférez un acteur européen, [eurocircuits](https://www.eurocircuits.com/) est un des acteurs reconnus.

[![IMAGE ALT TEXT](https://user-images.githubusercontent.com/21155051/227790488-3d505f7f-50a5-4423-a540-14bc276046c1.png)](http://www.youtube.com/watch?v=RXGGvsUtz0c "TUTO : faire fabriquer un produit LECTIX")

1. Télécherger les sources de ce produit en cliquant sur le bouton `Code`, puis `Download ZIP`.
1. Décompresser le dossier.
1. Les fichiers pour la fabrication se trouvent dans le répertoire `hardware/prod`.
1. Se connecter sur [https://cart.jlcpcb.com/quote](https://cart.jlcpcb.com/quote)
1. Cliquer sur le bouton `Add gerber file` et sélectionner le fichier `gerbers.zip`.
1. Sélectionnez la quantité de cartes que vous souhaitez dans le champs `PCB Qty`.
1. Laisser toutes les autres options par défaut, puis cliquez sur le toggle switch en face de `PCB Assembly`, et enfin sur le bouton `confirm`.
1. Une preview de la carte électronique sans les composants doit apparaitre. Cliquez sur `NEXT`.
1. Cliquez sur le bouton `Add BOM File`, puis sélectionnez le fichier `bom.csv`
1. Cliquez sur le bouton `Add CPL File`, puis sélectionnez le fichier `pos.csv`
1. **Vérifier que tous les composants sont en stock** et bien sélectionnés, puis cliquez sur `NEXT`.
1. Une preview de la carte avec ses composants apparait. Continuer le chemin en cliquant sur `NEXT`.
1. Le prix final apparait. Sélectionnez la catégorie du produit, puis cliquez sur `SAVE TO CART`.
1. Une fois sauvegardé dans votre panier, vous pouvez valider votre commande et choisir le moyen d'acheminement. Afin de ne pas avoir à se préoccuper des frais de douane, nous vous conseillons de choisir une méthode d'expédition DDP.

Vous receverez vos cartes sous 1 à 3 semaines. 

**Nous ne sommes en aucun cas responsables des cartes qui arriveraient défectueuses ou non fonctionnelles.**

### Modifications des fichiers sources

Installez kicad 6 (ou version supérieure), et ouvrez le fichier LEC009002.kicad_pro

### Programation

Pour programmer le module, vous devez posséder
- un programmateur AVR type USBASP
- Un adaptateur 10 pin vers 6 pin
- Un connecteur de type header 2 x 6 pour connecter l'adaptateur à la carte

Le firmware se trouve dans le dossier du même nom. Il est recommandé d'utiliser VS-code et platform-io pour programmer la carte. Pour ce faire, branchez le programmateur à votre PC et à la carte à programmer, puis rentrer les commandes suivantes :

```
cd firmware
platformio run --target fuses && platformio run --target upload
```

### Regénérer les fichiers gerber, BOM, et position (Optionnel)

Peut se faire simplement en utilisant kikit :

```
cd hardware
docker run --rm -w /kikit -v $PWD:/kikit yaqwsx/kikit kikit fab jlcpcb --assembly --no-drc --schematic LEC009002.kicad_sch --field LCSC --corrections JLCPCB_CORRECTION --nametemplate LEC009002_{} LEC009002.kicad_pcb prod/

```
## Notices
[Manuel FR](docs/manual_fr.pdf)

## License
Tous nos fichiers sont plubliés sous les licenses
- CERN Open Hardware Licence Version 2 - Strongly Reciprocal pour ce qui touche au hardware
- GNU General Public License v3.0 pour tout ce qui est software