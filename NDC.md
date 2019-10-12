#### LO21
# Note de clarification 

##### Sujet : Trading Simulator

##### Objectif : ​ Réaliser une application qui permet de simuler des stratégies de trading

## 1 - Description des fonctions principales

    - Cotation: valeur relative d’une monnaie contre une autre
    - Devise de base 
    - Devise de contrepartie
    - Paire de devise (relation en les 2 devises)
        - Surnom

    Exemple: 
        EUR/USD
	    BTC/USD 3937 : 1 bitcoin = 3937$
	    EUR/RUB : a comme surnom “Betty”

    La cotation subit des variations au cours de la journée:
        - Prix d’ouverture (Open price): prix du 1er échange
        - Prix le plus haut (High price): prix le plus haut atteint
        - Prix le plus bas (Low price): prix le plus bas atteint
        - Prix de fermeture (Close price): prix du dernier échange
        - Volume (V): volume échangé au cours de la journée
    
    Ces 4 données sont nommées OHLC.

**Bougie**

    La bougie représente ces 4 données:
        - Le corps de la bougie: variation Open & Close price
        - Mèche du haut: High price
        - Mèche du bas: Low price
    
**Couleur de la bougie:**

    Rouge: Baisse entre Open & Close price
        - Taille du corps: (Open price - Close price)
        - Taille mèche haute: (High price - Open price)
        - Taille mèche basse: (Low price - Close price)
    Verte: hausse entre Open & Close price
        - Taille du corps: (Open price - Close price)
        - Taille mèche haute: (High price - Open price)
        - Taille mèche basse: (Low price - Close price)
        
**Inteprétation Bougie**

    - Corps de la bougie:
        - Corps grand: forte évolution du prix 
    
    - Mèche haute:
        - Mèche grande: forte augmentation du prix puis rétraction
    
    - Mèche basse:
        - Mèche grande: forte diminution du prix puis remonté 
    
Une bougie avec petite mèche haute, petit corps, petite mèche basse indique qu’il ne s’est rien passé dans la journée.
    
    
**Analyse des bougies:**
    
    Toupies:
        - Corps de petite taille comparé à leur mèches 
        - Open price ~ Close price
    
    Doji: (cas particulier toupie)
        - Open price = Close price
    
    Le marteau: 
        - Toupie à mèche basse 
        - Tendance baissière
        - Rebond technique le lendemain
    
    Etoile filante:
        - Toupie à mèche haute 
        - Tendance haussière
        - Pris de bénéfice le lendemain
    
    Pendu:
        - Toupie à mèche basse
        - Tendance haussière
        - Fin de tendance haussière si bougie noire le lendemain

## 2 - Description des fonction principales

**2.1 Affichage des données**

    Chargement d’un fichier .csv comprenant:
        - 4 données OHLC
        - Volume
        - Date

    Affichage:
        - 1er onglet: Graphique en chandelier -> Données OHLC
        - 2eme onglet: Graphique en barre -> volume

**2.2 choix des paramètres:** 
    
    Après chargement du fichier:
        - Choix de la date de simulation (par défaut: date début données)
        - Montant devise de base (0 par défaut)
        - Montant devis de contrepartie (1000000 par défaut)
    
    Intermédiaire permet de réaliser des transactions:
        - Type: Broker ou plateforme
        - Rémunération: 0.1% par défaut
    
    Transaction: 
        - achat: pourcentage sur devises de bases reçues 
        - vente: pourcentage sur devises de contrepartie reçues
    
**2.3 Stratégie de trading**
    
    Tableau contenant les informations sur les achats et ventes de l’utilisateur:
        - Date de la transaction
        - Montant total de la devise de cotation + différence liée à la dernière transaction (positive si achat, négative si vente)
        - Montant total de la devise de base + différence liée à la dernière transaction (positive si vente, négative si achat)
        - Retour sur investissement total (ROI): Ratio entre montant total suite à la dernière transaction et le montant de départ de la simulation
    
    Transaction réalisée sur:
        - open price + date
    Montant total exprimé en devise de cotation
    Conversion devise de base vers devise de contrepartie est réalisée avec close price
    
**2.4 Mode Manuel**
    
    L’utilisateur lance la simulation en mode manuel est choisi:
    Dates d’achat et date de vente
    Annuler la dernière transaction
    
**2.5 Mode Automatique**
    
    L’utilisateur sélectionne une stratégie de trading parmi une liste.
    Stratégie requiert :
        - date début de la simulation
        - date de fin de la simulation
    
    Chaque journée, la décision d’acheter ou de vendre ce fait avec:
        - données OHLCV des journées passées
        - Open price de la journée courante (prix d’achat/vente)
        - Montants disponibles pour la devise de base et de contrepartie
    
**2.6 Éditeur de texte**
    
    Prise de note sur la stratégie qu’il test, avec sauvegarde:
        - Fichier de données
        - Tableau achats/ventes
        - Notes prises dans l’éditeur
    
**2.7 Indicateurs techniques**

    Informations dérives des informations OHLCV + aide à la décision
        - Exponential Moving Average (EMA)
        - Relative Strength Index (RSI)
        - Moving Average convergence Divergence (MACD)
    
    Exemple: RSI varie entre 0 et 100: Achat <20 ou vente >80
    
**2.8 Analyse de forme**

    Détecter et afficher des formes connues de bougies (sur demande de l’utilisateur)
    
**2.9 Mode pas à pas**

    Information connue: Jour courant: Open Price
    Décision d’achat ou de vente (sans info futures)
    Peut revenir en arrière (supprime la transaction du jour courant)
    
**2.10 Evolution de l’application**

    Les choix de conception devront donc permettre de rendre l’application évolutive et notamment garantir la facilité d’ajout des composants suivants : 
        - Modifier facilement le format des données fournie en entrée.
        - Ajouter facilement des stratégies automatiques de trading.
        - Ajouter facilement des indicateurs. Vous êtes libre d’organiser votre interface du moment qu’elle permet piloter facilement l’application. 


