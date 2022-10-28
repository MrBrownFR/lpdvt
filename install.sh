# Shell permettant l'installation du programme d'info

echo """
 ██████╗  ██████╗ ██╗
██╔════╝ ██╔═══██╗██║
██║  ███╗██║   ██║██║
██║   ██║██║   ██║██║
╚██████╔╝╚██████╔╝███████╗
 ╚═════╝  ╚═════╝ ╚══════╝
"""

echo """La prépa dans votre terminal
============================"""

PCKG_MANAGER="None"

echo
echo


echo """Etapes de l'installation:
-------------------------
1. Téléchargeent du repo dans un dossier adapté
2. Téléchargement des dépendances nécéssaires
"""

echo "Quelle distribution utilisez-vous? "
select DISTRIB in "Ubuntu (WSL)" "Fedora"; do

    case $DISTRIB in
        "Ubuntu (WSL)")
            PCKG_MANAGER="apt"
            break;;
        "Fedora")
            PCKG_MANAGER="dnf"
            break;;
        *)
            echo "Ce nombre n'était pas dans la liste :/";;
    esac

done
echo "Merci beaucoup, on va pouvoir commencer ;) détendez-vous et regardez la magie opérer! (on va juste vous demander votre mot de passe pour installer des trucs, mais rien de méchant :))"
echo

echo """
1. Clonage du projet
--------------------
    a. Installation de git
    b. Clonage du projet dans le \$HOME
"""

# LOGIQUE PRINCIPALE
rm -rf ~/lpdvt
sudo $PCKG_MANAGER install git -y && git clone https://github.com/MrBrownFR/lpdvt.git ~

echo """

2. Compilation du programme
--------------------
    a. Installation des dépendances
    b. Compilation
"""
sudo $PCKG_MANAGER install gcc libasan libubsan -y && gcc -std=c99 -Wall -Wextra -Werror -fsanitize=address,undefined -o ~/.local/bin/lpdvt ~/lpdvt/main.c

echo "Et voilà le travail ;) maintenant que le programme est installé, vous pouvez l'éxécuter juste en tapant \033[1mlpdvt\033[0m dans votre terminal!"
