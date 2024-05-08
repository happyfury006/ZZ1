-- Q1-Créer les tables de la base de données :
CREATE TABLE VIN(
  VNUM NUMBER(2,0) CONSTRAINT PK_VIN PRIMARY KEY,
  VNOM VARCHAR2(30) CONSTRAINT VNOM_NOTNULL NOT NULL,
  CEPAGE VARCHAR2(30));

CREATE TABLE INSPECTEUR(
  INUM NUMBER(2,0) CONSTRAINT PK_INSPECTEUR PRIMARY KEY,
  INOM VARCHAR2(30) CONSTRAINT INOM_NOTNULL NOT NULL);

CREATE TABLE TEST(
  VNUM NUMBER(2,0),
  INUM NUMBER(2,0),
  NOTE NUMBER(2,0) CONSTRAINT NOTE_NOTNULL NOT NULL,
  TDATE DATE,
  CONSTRAINT PK_TEST PRIMARY KEY(VNUM, INUM),
  CONSTRAINT FKVNUM_TEST FOREIGN KEY(VNUM) REFERENCES VIN(VNUM),
  CONSTRAINT FKINUM_TEST FOREIGN KEY(INUM) REFERENCES INSPECTEUR(INUM));

-- Q2-Ajouter une contrainte dans la table TEST pour indiquer que la note doit être comprise entre 0 et 10.
ALTER TABLE TEST ADD CONSTRAINT BORNES CHECK(0<NOTE<10).
-- Q3-En utilisant les tables USER_CONSTRAINTS et USER_CONS_COLUMNS du catalogue Oracle,
-- retrouver toutes les contraintes qui ont été définies sur la table TEST.

-- Q4-Insérer les données des tables VIN et INSPECTEUR :

INSERT INTO VIN VALUES(1,'Cave de Macon','Chardonnay');
INSERT INTO VIN VALUES(2,'Merlot','Cabernet Sauvignon');
INSERT INTO VIN VALUES(3,'Pinot Noir','Pinot Noir');

INSERT INTO INSPECTEUR VALUES(1,'Magouille');
INSERT INTO INSPECTEUR VALUES(2,'Intransigeant');
INSERT INTO INSPECTEUR VALUES(3,'Sympa');
INSERT INTO INSPECTEUR VALUES(4,'Cool');

-- Q5-Insérer les données de la table TEST en utilisant la fonction TO_DATE (valider votre transaction à la fin).
INSERT INTO TEST VALUES(1,1,7,TO_DATE('10/04/2009','DD-MM-YY'));
INSERT INTO TEST VALUES(2,1,8,TO_DATE('15/05/2009','DD-MM-YY'));
INSERT INTO TEST VALUES(2,2,4,TO_DATE('20/05/2009','DD-MM-YY'));
INSERT INTO TEST VALUES(2,3,9,NULL);
-- Q6-Vérifier le contenu des tables.
-- (Pour la table TEST, utiliser TO_CHAR pour afficher la date correctement.)
SELECT VNUM,INUM,NOTE,TO_CHAR(TDATE)
FROM TEST;

-- Q7-Insérer le tuple (2, Rigolo) dans la table INSPECTEUR.
-- Que se passe-t-il ? Pourquoi ?
INSERT INTO INSPECTEUR VALUES(2,Rigolo);
--NOMBRE DE VALEURS INSUFFISANT

-- Q8-Insérer le tuple (5, 2, 8, 01/01/2010) dans la table TEST.
-- Que se passe-t-il ? Pourquoi ?
 INSERT INTO TEST VALUES(5, 2, 8, 01/01/2010);
 --TYPE DE DONNEE INCOHERENTE

-- Q9-Insérer un nouvel inspecteur dans la table INSPECTEUR,
-- à savoir l’inspecteur de numéro 5 et dont on a égaré le nom.
-- Que se passe-t-il ? Pourquoi ?
 INSERT INTO INSPECTEUR VALUES(5,NULL);
 
-- Q10-Supprimer le vin n°2. Que se passe-t-il ?  Pourquoi ?  
DELETE FROM VIN
WHERE VNUM='2';

-- Q11-Modifier les contraintes d’intégrité définies sur la table TEST pour
-- obtenir la suppression des tests d’un vin lorsque celui-ci est supprimé de la table VIN.
-- (Pour modifier une contrainte, il faut la supprimer puis la recréer).
ALTER TABLE TEST  DROP CONSTRAINT FKVNUM_TEST;
ALTER TABLE TEST  ADD CONSTRAINT FKVNUM_TEST FOREIGN KEY(VNUM)  REFERENCES VIN(VNUM) ON DELETE CASCADE;
-- Q12-Supprimer à nouveau le vin n°2 et vérifier la suppression de ses tests.
DELETE FROM VIN
WHERE VNUM='2';

SELECT *
FROM TEST;

SELECT *
FROM VIN;

-- Q13-Réinsérer le vin 2 ainsi que ses tests dans les tables associées.
INSERT INTO VIN VALUES(2,'Merlot','Cabernet Sauvignon');
INSERT INTO TEST VALUES(2,1,8,TO_DATE('15/05/2009','DD-MM-YY'));
INSERT INTO TEST VALUES(2,2,4,TO_DATE('20/05/2009','DD-MM-YY'));
INSERT INTO TEST VALUES(2,3,9,NULL);

-- Q14-Faire les modifications de structure pour permettre l’insertion du numéro
-- de téléphone ’03-85-44-12-09’ pour l’inspecteur n°3.
-- Que se passe t-il pour les autres inspecteurs ?
ALTER TABLE INSPECTEUR ADD (NUMTEL VARCHAR2(14) DEFAULT NULL);

UPDATE INSPECTEUR set NUMTEL='03-85-44-12-09' WHERE INUM=3;
-- Q15-Faire les modifications de structure pour réduire la longueur de INOM à 6 caractères.
-- Prévoir la récupération des valeurs de cette colonne en les tronquant à 6 caractères.
UPDATE INSPECTEUR SET INOM=SUBSTR(INOM,1,6);
ALTER TABLE INSPECTEUR ADD CONSTRAINT LONGUEURNOM CHECK(LENGTH(INOM)<7);
-- Q16-Créer la vue SYNTHESE09 regroupant les attributs CEPAGE, VNUM, VNOM, INOM, NOTE et TDATE pour tous les tests effectués en 2009.
-- Vérifier que la vue a bien été créée.
-- Afficher le contenu de cette vue.
-- Donner la note moyenne de chaque vin en 2009. On précisera le nom du vin.
CREATE VIEW SYNTHESE09 AS 
SELECT V.CEPAGE, V.VNUM,V.VNOM,I.INOM,T.NOTE,T.TDATE
FROM VIN  V 
JOIN TEST  T 
ON V.VNUM=T.VNUM
JOIN INSPECTEUR  I 
ON I.INUM=T.INUM
WHERE TO_DATE(T.TDATE,'YYYY')=TO_DATE(2009,'YYYY');



-- Q17-Afin d’optimiser les temps de réponse, indexer les cépages dans la table VIN.

-- Q18-Afin d’optimiser les temps de réponse, indexer également les cépages dans la vue SYNTHESE09.
-- Que se passe t’il ? Pourquoi ?

-- Q19-Insérer les trois tuples (10, Relax), (11, Pointu) et (12, Odieux) dans la table INSPECTEUR.
-- Vérifier que tout s’est bien passé.
-- Annuler la dernière transaction et vérifier à nouveau le contenu de la table INSPECTEUR. 

-- Q20-Modifier les instructions de Q19 de manière à ce que la table INSPECTEUR
-- contienne les inspecteurs Pointu et Relax suite à l’annulation de la dernière transaction.
-- Vous devez conserver les 3 ordres insert. 

-- Q21-Executer le trigger suivant :
CREATE OR REPLACE TRIGGER VerifCepage
BEFORE INSERT OR UPDATE OF CEPAGE ON VIN FOR EACH ROW
BEGIN
  IF :NEW.CEPAGE = 'Pinot' THEN :NEW.CEPAGE := 'Pinot Noir';
  END IF;
END VerifCepage;
/

-- Q22-Insérer le tuple (5, 'Cotes de la Charité', 'Pinot') dans la table VIN.
-- Que se passe-t-il ? Pourquoi ?

-- Q23-Modifier le tuple pour mettre Pinot.

-- Q24-Executer le trigger suivant :
CREATE OR REPLACE TRIGGER VerifChardonnay
BEFORE INSERT OR UPDATE ON TEST FOR EACH ROW
DECLARE
      V_CEPAGE VARCHAR2(30);
      V_INOM VARCHAR2(30);
BEGIN
  SELECT CEPAGE INTO V_CEPAGE
  FROM VIN
  WHERE VNUM=:NEW.VNUM;
  IF V_CEPAGE='Chardonnay' THEN
    SELECT INOM INTO V_INOM
    FROM INSPECTEUR
    WHERE INUM=:NEW.INUM;
    IF (V_INOM!='Cool' AND V_INOM!='Sympa') THEN
      RAISE_APPLICATION_ERROR(-20000,'Seuls les inspecteurs Cool et Sympa peuvent attribuer une note aux vins Chardonnay.');
    END IF;
  END IF;
END VerifChardonnay;
/
-- si erreur : SHOW ERRORS

-- Q25-Insérer le tuple (1, 2, 6, 10/04/2009) dans la table TEST.
-- Que se passe-t-il ? Pourquoi ?

-- Q26-Insérer le tuple (3, 3, 8, 15/04/2009) dans la table TEST.
-- Que se passe-t-il ? Pourquoi ?

-- Q27-Insérer le tuple (1, 3, 6, 20/04/2009) dans la table TEST.
-- Que se passe-t-il ? Pourquoi ?

-- Q28-Nous avons fait une erreur, en fait c'était l'inspecteur 2 qui avait mis la note.
-- Corriger. Que se passe-t-il ? Pourquoi ?

-- Q29-Observer les tables que vous avez créez dans USER_CATALOG ou CAT (synonyme).

-- Q30-Supprimer la table INSPECTEUR. Que se passe-t'il ? Pourquoi ?

-- Q31-Supprimer la table TEST puis interroger la vue SYNTHESE09.
-- Que se passe-t'il ?

-- Q32-Vider la table VIN. Vérifier que tout s’est bien passé.

-- Q33-Supprimer les tables VIN et INSPECTEUR. Vérifier que tout s’est bien passé.
