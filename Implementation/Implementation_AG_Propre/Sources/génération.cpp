//////////////////////////////////////////////////
/// Projet S6 - Sujet 4 - Algorithme Génétique ///
///              génération.cpp                ///
//////////////////////////////////////////////////
#include "../Headers/génération.h"


/**** STATIC ****/

float Population::probaCroisement = -1.0;
int Population::nombreIndividus = -1;
int Population::nombreGenerationMax = -1;
int Population::nombreCriteres = -1;
int* Population::criteres = nullptr;
string Population::fitness1 = "";
string Population::fitness2 = "";
float Population::valeurApprochee = -1.0;
float Population::valeurApprochee2 = -1.0; ///pas dans le cds///

int Population::numeroGeneration = 0;

/**** CONSTRUCTEURS****/

Population::Population() : ensemble(0) //test OK
{
	numeroGeneration += 1;
	//std::cout<<"CREATION SUCCESS"<<endl;
}

Population::Population(Population const& P) : ensemble(P.ensemble) //test OK
{
	numeroGeneration += 1;
	//std::cout<<"CREATION SUCCESS"<<endl;
	
}

Population::Population(string* const& donnees) :  ensemble(0) //test OK
{

	/*std::cout<<"Donnees recues par le constructeur :"<<std::endl;
    std::cout<<"proba croisement = "<<std::stof(donnees[0],nullptr)<< std::endl;
    std::cout<<"taille population = "<<std::stoi(donnees[1], nullptr, 10)<<"  nombre de Generation Max = " <<std::stoi(donnees[2], nullptr, 10)<<std::endl;
    std::cout<<"nombre de critères = "<<std::stoi(donnees[3], nullptr, 10)<<" critère 1 = "<<std::stoi(donnees[4], nullptr, 10)<<"  critère 2 = "<<std::stoi(donnees[5], nullptr, 10)<<std::endl;
    std::cout<<"fitness1 = "<<donnees[6]<<" fitness2 = "<<donnees[7]<<std::endl;
    std::cout<<"valeurApprochee1 = "<<std::stof(donnees[8], nullptr)<<" valeurApprochee2 = "<<std::stof(donnees[9], nullptr)<<std::endl;*/

	/** INITIALISATION DES DONNEES INVARIABLES **/
	QString tmp=QString::fromStdString(donnees[0]);
	probaCroisement = tmp.toFloat(); // string to float
	nombreIndividus = std::stoi(donnees[1], nullptr, 10);
	nombreGenerationMax = std::stoi(donnees[2], nullptr, 10);	
	nombreCriteres = std::stoi(donnees[3], nullptr, 10);

	/** INITIALISATION DES DONNEES VARIABLES **/
	if(nombreCriteres == 1 || nombreCriteres == 2){
		if(nombreCriteres == 1){ 							 //si on à un seul critere
			criteres = (int*)malloc(nombreCriteres*sizeof(int)); //initialisation de la taille du tableau de criteres
			criteres[0] = std::stoi(donnees[4], nullptr, 10);    //initialisation du critere
			fitness1 = donnees[6];                               //initialisation de la fonction fitness

			if (criteres[0] == 3)		{//si le critere est la recherche d'une valeur approchée
				tmp=QString::fromStdString(donnees[8]);
				valeurApprochee = tmp.toFloat();//initialisation de la valeur approchée
			}

		}
		else {
			criteres = (int*)malloc(nombreCriteres*sizeof(int)); //initialisation de la taille du tableau de criteres
			criteres[0] = std::stoi(donnees[4], nullptr, 10);    //initialisation du critere 1
			criteres[1] = std::stoi(donnees[5], nullptr, 10);    //initialisation du critere 2
			fitness1 = donnees[6];                               //initialisation de la fonction fitness 1
			fitness2 = donnees[7];                               //initialisation de la fonction fitness 2
	
			if (criteres[0] == 3)	{							 //si le critere 1 est la recherche d'une valeur approchée
				tmp=QString::fromStdString(donnees[8]);
				valeurApprochee = tmp.toFloat();//initialisation de la valeur approchée 1
			}
			if (criteres[1] == 3)	{							 //si le critere  2est la recherche d'une valeur approchée
				tmp=QString::fromStdString(donnees[9]);
				valeurApprochee = tmp.toFloat();//initialisation de la valeur approchée 2
			}
		}
		numeroGeneration += 1;
	}
	else std::cerr<<"nombre de critères non conforme"<<std::endl;

	/*POPULATION INITIALE*/
	/*float idonnees[3];
    idonnees[0] = 4.0;
    idonnees[1] = 0.01;
    idonnees[2] = 1.0;*/
	for(int i = 0; i < nombreIndividus; i++){
		Individu *nouv = new Individu(lireInitialisation(donnees[10]));
		ensemble.push_back(nouv);
	}
	//std::cout<<"CREATION SUCCESS"<<endl;
}


/**** DESTRUCTEUR ****/

Population::~Population() //a revoir
{
	//~ cout<<"DESTRUCTEUR POPULATION"<<endl;
	int size = ensemble.size();
	for(int i = size; i >= 0; i--){
		//delete ensemble[i];
		ensemble.pop_back();
	}
}

/**** GETTEURS ****/

int Population::getNombreIndividus(){
	return this->nombreIndividus;
}

int Population::getNumeroGeneration(){
	return this->numeroGeneration;
}

string Population::getFitness1(){
	return this->fitness1;
}

string Population::getFitness2(){
	return this->fitness2;
}

float Population::getValeurApprochee(){
	return this->valeurApprochee;
}

float Population::getValeurApprochee2(){
	return this->valeurApprochee2;
}

vector<Individu*> Population::getEnsemble(){
	return this->ensemble;
}

int Population::getNombreGenerationMax(){		//fonction qu'on a oubliée dans le cds :(
	return this->nombreGenerationMax;
}

/// UTILE DANS ecrirePopulation POUR RECUPERER LE NOMBRE DE CRITERES

int Population::getNombreCriteres(){			//fonction qu'on a oubliée dans le cds :(
	return this->nombreCriteres;
}

/// PAS DANS LE CDS (mais inutiles pour l'instant donc maybe on est bon quand même)

/*
int[] Population::getCriteres(){				//fonction qu'on a oubliée dans le cds :(
	return this->criteres;
}

float Population::getProbaCroisement(){			//fonction qu'on a oubliée dans le cds :(
	return this->probaCroisement;
}*/

/**** SETTEURS ****/

void Population::setNombreIndividus(int nbIndiv){
	this->nombreIndividus = nbIndiv;
}

void Population::setNumeroGeneration(int num){
	this->numeroGeneration = num;
}

void Population::setFitness1(string fit1){
	this->fitness1 = fit1;
}

void Population::setFitness2(string fit2){
	this->fitness2 = fit2;
}

void Population::setValeurApprochee(float val){
	this->valeurApprochee = val;
}

void Population::setValeurApprochee2(float val){
	this->valeurApprochee2 = val;
}

void Population::setProbaCroisement(float proba){
	this->probaCroisement = proba;
}

void Population::setNombreGenerationMax(int nb){
	this->nombreGenerationMax = nb;
}

void Population::setEnsemble(Individu &nouv){
	this->ensemble.push_back(&nouv);
}



/**** TESTS ****/

bool Population::testArret(string nomFichierSortie) //pourquoi ça doit renvoyer un population? || a finir || à modifier en transformant en bool
{  
	if(!this->testConvergence(nomFichierSortie) && this->testNombreGeneration()){
		//calculerEcrireStats(p,nomFichierSortie+"/"+nomFichierSortie+"_Populations.txt",nomFichierSortie+"/"+nomFichierSortie+"_Stats.txt");
		return true;
	}
	else {
		return false;
	}

}

bool Population::testConvergence(string nomFichierSortie) //Test OK
{
	std::cout<<"TEST CONVERGENCE"<<std::endl;
	//~ numeroGeneration = 5; //a virer après les tests
	if(numeroGeneration < 5)
		return false;
	float *TestTab;
	FILE *f;
    //~ std::cout<<"nombre de criteres : "<<nombreCriteres<<std::endl;
    //~ std::cout<<"numero generation : "<<numeroGeneration<<std::endl;
    
    string StatFile = nomFichierSortie+"/"+nomFichierSortie+"_Stats.txt";
    f=fopen(StatFile.c_str(), "r");
    for(int i = 0; i < numeroGeneration-5; i ++) {
			TestTab=lireStat(f);
			delete[] TestTab;
		
	}
	
	float temp[5];
	float tempCrit1[5];
	float tempCrit2[5];
	
	for(int k = 0; k < 5; k ++)
	{
		TestTab = lireStat(f);
			if (nombreCriteres == 1){
				temp[k] = TestTab[0];
				//~ std::cout <<"Temp["<<k<<"] : "<<temp[k]<<std::endl;
			}
			else{ 
				tempCrit1[k] = TestTab[0];
				tempCrit2[k] = TestTab[3];
				//~ std::cout <<"TempCrit1["<<k<<"] : "<<k<<std::endl;
				//~ std::cout <<"TempCrit2["<<k<<"] : "<<k<<std::endl;
			}
		//~ std::cout << std::endl;
		delete[] TestTab;
	}
	//~ std::cout<<std::endl;
	
	for(int i = 4; i > 0; i --){
		if(nombreCriteres == 1){
			if(!((temp[i] <= (temp[i-1] + 0.015*temp[i-1])) && (temp[i] >= (temp[i-1] - 0.015*temp[i-1]))))
				return false;
			
			//~ std::cout <<"Temp["<<i<<"] : "<<temp[i]<<std::endl;	
		}
		else if(nombreCriteres == 2){
			if(!(((tempCrit1[i] <= (tempCrit1[i-1] + 0.015*tempCrit1[i-1])) && (tempCrit1[i] >= (tempCrit1[i-1] - 0.015*tempCrit1[i-1])))&&((tempCrit2[i] <= (tempCrit2[i-1] + 0.015*tempCrit2[i-1])) && (tempCrit2[i] >= (tempCrit2[i-1] - 0.015*tempCrit2[i-1])))))
				return false;
			
			//~ std::cout <<"TempCrit1["<<i<<"] : "<<tempCrit1[i]<<std::endl;
			//~ std::cout <<"TempCrit2["<<i<<"] : "<<tempCrit2[i]<<std::endl;
		}
	}
	
	
	fclose(f);

	return true;
}


bool Population::testNombreGeneration()
{
	if (numeroGeneration < nombreGenerationMax)
		return true;
	return false;
}

bool Population::testPopulationRemplie(){
	if(ensemble.size() < (unsigned int)nombreIndividus)
		return true;
	return false;
}
/**** LES ALGOS ****/

void Population::evaluation() //test ok
{
	std::cout<<std::endl<<"EVALUATION"<<std::endl;
	string fitnessTmp;
	if (nombreCriteres == -1)
		std::cerr<<"nombre de critères non conforme"<<std::endl;
	else {		
		for (int iCritere = 0; iCritere < nombreCriteres; iCritere ++){
			//~ std::cout<<"criteres : "<<iCritere+1<<" / "<<nombreCriteres<<std::endl;
			for (unsigned int iIndiv = 0; iIndiv < ensemble.size(); iIndiv ++){
				//~ cout << "Individu " << iIndiv <<endl;
				if(iCritere == 0)
					fitnessTmp = this->fitness1;
				if(iCritere == 1)
					fitnessTmp = this->fitness2;
				//cout << "avant appel d'eval indiv" << endl;
				//cout << "fonction fitness : " << fitness1 << endl;
				ensemble[iIndiv]->Individu::evaluationIndividu(fitnessTmp, iCritere);
			}
			//~ std::cout<<"icritere : "<<iCritere<<std::endl;
			//~ std::cout<<"critere : "<<criteres[iCritere]<<std::endl;
			this->Population::triPopulation(iCritere);
			int cpt = 1;
			int ensembleSize = ensemble.size() - 1;
			float iScore1, iScore2;
			for(int iIndiv = 0; iIndiv < ensembleSize; iIndiv ++){
				iScore1 = ensemble[iIndiv]->Individu::getScore(iCritere);
				iScore2 = ensemble[iIndiv+1]->Individu::getScore(iCritere); 
				if(iScore1 == iScore2){	
					ensemble[iIndiv]->Individu::setRang(cpt, iCritere);
					
				}
				else {
					ensemble[iIndiv]->Individu::setRang(cpt, iCritere);
					cpt ++;
				}
			}
			iScore1 = ensemble[ensembleSize]->Individu::getScore(iCritere);
			iScore2 = ensemble[ensembleSize-1]->Individu::getScore(iCritere);
			cpt = ensemble[ensembleSize-1]->Individu::getRang(iCritere);
			if (iScore1 == iScore2){
				ensemble[ensembleSize]->Individu::setRang(cpt, iCritere);
			}
			else { 
				cpt ++;
				ensemble[ensembleSize]->Individu::setRang(cpt, iCritere);
			}
			//for(int i = 0; i < ensemble.size(); i++)
        	//	std::cout<<"rang pour critere "<<iCritere<< " : "<<ensemble[i]->getRang(iCritere)<<std::endl;
        	//for (int i = 0; i < ensemble.size(); i ++)
    		//	std::cout<<"critere : "<<iCritere<< " "<<ensemble[i]->getScore(iCritere)<<std::endl;

		}
	}
	//return *this;

}

void Population::maximisation(int indiceScore) //test OK, pas dans cds (ameliorable)
{
	std::cout<<"MAXIMISATION"<<std::endl;
	int taille = ensemble.size();
	bool tab_en_ordre = false;
    while(!tab_en_ordre)
	{	
		tab_en_ordre = true;
        	for(int i=0 ; i < taille-1 ; i++)
        	{
           		if(ensemble[i]->Individu::getScore(indiceScore) < ensemble[i+1]->Individu::getScore(indiceScore))
            		{
                		swap(ensemble[i],ensemble[i+1]);
                		tab_en_ordre = false;
            		}
        	}
        taille--;
    }
}

void Population::minimisation (int indiceScore)//test OK, pas dans cds (ameliorable)
{
	std::cout<<"MINISATION"<<std::endl;
	int taille = ensemble.size();
	bool tab_en_ordre = false;
    while(!tab_en_ordre)
	{	
		tab_en_ordre = true;
        	for(int i=0 ; i < taille-1 ; i++)
        	{
           		if(ensemble[i]->Individu::getScore(indiceScore) > ensemble[i+1]->Individu::getScore(indiceScore))
            		{
                		swap(ensemble[i],ensemble[i+1]);
                		tab_en_ordre = false;
            		}
        	}
        taille--;
    }
}

void Population::triValeur (int indiceScore)//test OK, pas dans cds (ameliorable)
{
	std::cout<<"VALEUR APPROCHEE"<<std::endl;
	float val=0;
	bool tab_en_ordre = false;
	if (indiceScore == 0)
		val = valeurApprochee;
	else if (indiceScore == 1)
		val = valeurApprochee2;
	else 
		std::cerr<<"error triPopulation"<<std::endl;

	int taille = ensemble.size();
	int difference;	

    for(int i=0 ; i < taille ; i++)
    {	
        if(val < ensemble[i]->Individu::getScore(indiceScore) ){
            difference = ensemble[i]->Individu::getScore(indiceScore) - val;
        }
        else{ 
            difference = val - ensemble[i]->Individu::getScore(indiceScore);
        }
        ensemble[i]->Individu::setRang(difference, indiceScore);
        //std::cout<<ensemble[i]->Individu::getRang(indiceScore)<<" pour "<<ensemble[i]->Individu::getScore(indiceScore)<<std::endl;
    }

    while(!tab_en_ordre)
	{	
		tab_en_ordre = true;
        for(int i=0 ; i < taille-1 ; i++)
        {
            if(ensemble[i]->Individu::getRang(indiceScore) > ensemble[i+1]->Individu::getRang(indiceScore))
            {
            	swap(ensemble[i],ensemble[i+1]);
               	tab_en_ordre = false;
            }
        }
      	taille--;
    }
}

void Population::triPopulation(int indiceScore) //test OK, signature modifiée / cds
{ 	
	/**A DECOMMENTER POUR TEST **/
	/*std::cout<<"TRI"<<std::endl;
	std::cout<<"indiceScore : "<<indiceScore<<std::endl;
	criteres = (int*)malloc(1*sizeof(int));
	criteres[indiceScore]=3;
	std::cout<<"critere de tri : "<<criteres[indiceScore]<<std::endl;
	~~~~~~~~~~~~~~FIN DU TEST **/
	if (criteres[indiceScore] == 1) //MAXIMISATION
	{
		Population::maximisation(indiceScore);
	}
	else if (criteres[indiceScore] == 2) //MINIMISATION
	{
		
		Population::minimisation(indiceScore);
	}
	else if (criteres[indiceScore] == 3) //VALEUR APPROCHEE
	{
		Population::triValeur(indiceScore);
	}
	else 
		std::cerr<<"error triPopulation"<<criteres[indiceScore] <<std::endl;
	//for (int i = 0; i < ensemble.size(); i ++)
    	//std::cout<<ensemble[i]->getScore(indiceScore)<<std::endl;
}

Individu* Population::selectionner(int iCritere){ //à implémenter , modifié / cds
		double somme = 0.0;
		double sommeFitness = 0.0;
		int j;
		for(j = 0; j < this->nombreIndividus; j++)	{		//on récupère la somme totale des scores
			sommeFitness += (double)1/ensemble[j]->Individu::getRang(iCritere);
			}
		double nbAlea = (double)(rand()%(int)(sommeFitness*10000))/10000;	//on tourne la roulette (rand) et on regarde où elle s'arrête
		j = 0;
		while(somme < nbAlea && j < this->nombreIndividus -1){			//on trouve l'individu qui se trouve là on la roulette s'est arrêtée
			somme += (double)1/ensemble[j]->Individu::getRang(iCritere);
			// cout<<j<<" / "<<somme<<" / "<<nbAlea<<endl;
			j++;
		}
		cout<<"selection : " << j<<endl;
		return this->ensemble[j];
}

int Population::nombreAlea(int inf, int sup) // test OK ? oui test ok 
{
	//inf++;	//parce qu'on ne veut pas que inf soit inclu
	return rand()%(sup+inf) - inf;
}


void Population::crossover(Individu *parent1, Individu *parent2){
	//~ cout<< "p1 ";
		//~ for(int j=0;j<parent1->getTailleIndividu();j++){ cout<< parent1->getChromosome()[j] << " / ";}
		//~ cout<<endl;
	//~ cout<< "p2 ";
		//~ for(int j=0;j<parent2->getTailleIndividu();j++){ cout<< parent2->getChromosome()[j] << " / ";}
		//~ cout<<endl;
	Individu *enfant1, *enfant2;
	if(parent1->probAlea(probaCroisement)){
		cout<<"crossover oui"<<endl;
		int ptcrois = nombreAlea(1,parent1->getTailleIndividu());
		//~ cout<<nombreIndividus<<endl;
		enfant1=new Individu(parent1->getTailleIndividu());
		enfant2=new Individu(parent1->getTailleIndividu());
		for(int i = 0; i < ptcrois ;i++){
			enfant1->setGene(parent1->mutation(parent1->getGene(i)), i);
			enfant2->setGene(parent2->mutation(parent2->getGene(i)), i);
		}
		for(int i = ptcrois ; i < enfant1->getTailleIndividu() ; i++){
			enfant1->setGene(parent2->mutation(parent2->getGene(i)), i);
			enfant2->setGene(parent1->mutation(parent1->getGene(i)), i);
		}
	}
	else{
		cout<<"crossover non"<<endl;
		enfant1 = new Individu(*parent1);
		enfant2 = new Individu(*parent2);
	}
		//~ cout<< "e1 ";
		//~ for(int j=0;j<enfant1->getTailleIndividu();j++){ cout<< enfant1->getChromosome()[j] << " / ";}
		//~ cout<<endl;
		//~ cout<< "e2 ";
		//~ for(int j=0;j<enfant2->getTailleIndividu();j++){ cout<< enfant2->getChromosome()[j] << " / ";}
		//~ cout<<endl;
	if(testPopulationRemplie() ) ensemble.push_back(enfant1);
	if(testPopulationRemplie() ) ensemble.push_back(enfant2);
}


Population* Population::creerGeneration(Population *P){
	for(int i=0;testPopulationRemplie();i++){
		if(P->getNombreCriteres()==1)
			this->crossover(P->selectionner(0),P->selectionner(0));		//la population avec deux nouveaux individus
		else {
			if(i<P->getNombreIndividus()/2) this->crossover(P->selectionner(0),P->selectionner(0));
			else this->crossover(P->selectionner(1),P->selectionner(1));
		}
	}
	
	return this;
}
