## Indicateurs techniques 

#### Exponential Moving Average (EMA)

Une moyenne mobile est la valeur moyenne d’un actif sur une période révolue donnée. La moyenne mobile peut se calculer sur n’importe laquelle de ces valeurs mais on utilise traditionnellement le cours de fermeture. Ce type de moyenne est dite mobile en raison du fait qu’elle évolue chaque fois que l’unité de temps sur laquelle se base la moyenne s’achève. Elle "glisse" donc d’une unité de temps en intégrant dans son calcul, le cours sur la nouvelle période écoulée et en supprimant le dernièr cours. 
L'EMA accorde plus de poids aux cours de clôture les plus récents. L'exponentielle permet d’accorder encore plus de poids aux cours les plus récents, sans toutefois supprimer complètement le poids des valeurs plus anciennes en appliquant une pondération qui décroît exponentiellement.
Le moyenne mobile exponentielle se calcule selon la formule suivante :

``EMA(p) = (Dernier cours - (EMA(p) de la veille))*K + (EMA(p) de la veille)``

où K = 2/(p+1) et p = période de calcul 

##### Identifier des tendances et leurs forces

En lissant les variations du cours d’un actif, les moyennes mobiles permettent de se débarrasser du bruit de fond et donc de rendre la lecture des tendances plus facile. Lorsque le cours évolue en tendance, il est même possible en fonction de la pente de déterminer la force de la tendance en cours et d’appréhender tout essoufflement qui pourrait conduire à un renversement. 
Identifier des signaux d’achat / vente
Des signaux d’achat / vente peuvent aussi être déduits d’une analyse des moyennes mobiles. 
- Une première méthode consiste à prendre position en fonction du croisement de la moyenne mobile avec le cours : lorsque le cours coupe la moyenne mobile de bas en haut, alors on passe à l’achat ; à l’inverse si le cours coupe la moyenne mobile de haut en bas alors on passe à la vente. Il faut tenir compte de la moyenne mobile utilisée, l'EMA étant plus réactive que la moyenne mobile arithmétique mais avec un taux de faux signaux plus élevé.
- Une deuxième méthode consiste à utiliser 2 moyennes mobiles avec des périodes différentes. On utilise alors comme signal les croisements, les intersections de ces deux moyennes mobiles : lorsque la moyenne mobile disposant de la période la plus courte coupe de bas en haut la courbe de la moyenne mobile à plus long terme, alors on dispose d’un signal d’achat et inversement si le franchissement se fait de haut en bas (signal de vente).

#### Relative Strength Index (RSI)

C’est un indicateur de la tendance passée d’une série chronologique, sur un intervalle de temps donné. Le but du RSI est de fournir une information concentrée au lecteur, qui traduise de façon simple, rapide et synthétique, l’évolution passée du sous-jacent observé, sur les X derniers points relevés. Il faut bien comprendre que le RSI n’est qu’un simple filtre, qui ne fait que restituer l’information passée sous une forme différente, plus "conviviale" et rapidement interprétable. 
Voici la formule pour calculer le RSI sur les X derniers points :

``RSI(X) = 100 * H(X) / (H(X) - B(X))``

avec :
H(X) = hausse moyenne sur les X derniers points

B(X) = baisse moyenne sur les X derniers points

X peut être exprimé en jours, en heures, en minutes. 

Pour calculer H(X) et B(X), plusieurs méthodes sont possibles :
- un décompte des évolutions positives et négatives 
- la moyenne simple, dite arithmétique 
- la moyenne pondérée, dite exponentielle.

##### Paramétrages

- choix de l'unité de temps: par jour
- choix de la période: RSI14 calculé sur les 14 derniers points

##### Interprétations

- zone de sur vente: RSI < 30, excès baissier: le cours a bien chuté et devrait rebondir
- zone neutre vendeuse: 30 < RSI < 50, courant vendeur, sans excès 
- zone neutre acheteuse: 50 < RSI < 70, excès baissier: le cours a bien chuté et devrait rebondir
- zone de sur achat: RSI > 70, excès haussier: le cours a bien progressé et devrait corriger ?

Si le cours baisse et que le RSI part dans la zone des 30, il va falloir surveiller le retour au dessus des 30 pour jouer le rebond et passer à l’achat.
A l’inverse, si le cours monte et que le RSI passe dans la zone des 70, il falloir attendre qu’il revienne sous les 70 pour jouer la correction et passer à la vente. 

#### Moving Average Convergence Divergence (MACD)

La MACD, pour Moving Average Convergence Divergence, est un indicateur boursier très populaire, notamment auprès des traders à court terme. Cet indicateur s’appuie sur la différence entre 2 moyennes mobiles. 
Pour calculer la MACD il faut au préalable calculer deux Moyennes Mobiles Exponentielles (MME) sur des périodes de temps différentes : on utilise couramment les périodes de 12 et 26 jours car ce sont les périodes définies dans la version originale du MACD par son inventeur. 
Ces moyennes mobiles exponentielles sont calculées selon la formule suivante :

``MME = (fermeture du jour*0.09) + (MM de la veille * 0.91)``

La MACD résulte ensuite simplement de la différence entre les deux moyennes mobiles exponentielles calculées précédemment. 
Il existe deux modes d’utilisation de la MACD : 
- les croisements: L’indicateur présenté précédemment n’est complet que lorsqu’il est associé à une MME plus courte calculée sur les cours de fermeture des 9 dernières périodes (MME9). La MME9 définit alors une ligne dite "de signal" qui, en fonction de son franchissement par la MACD, donne un signal d’achat ou de vente à découvert : c’est la méthode dite des croisements ou des franchissements. Chaque fois que la courbe bleue (MACD) franchit la courbe rouge(MM9) de bas en haut, on obtient un signal d’achat.
A l’inverse, si la courbe bleue franchit la courbe rouge de haut en bas, on considère que c’est un signal de vente.
- les divergences: Les divergences entre le cours de l’actif et la différence entre la MACD et la courbe de signal permettent de déterminer l'essoufflement d’une tendance et donc de prévoir un éventuel retournement / changement de tendance. 
