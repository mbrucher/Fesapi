/*-----------------------------------------------------------------------
Copyright F2I-CONSULTING, (2014) 

philippe.verney@f2i-consulting.com

Ce logiciel est un programme informatique servant à accéder aux données formatées à l'aide des standards Energistics. 

Ce logiciel est régi par la licence CeCILL-B soumise au droit français et
respectant les principes de diffusion des logiciels libres. Vous pouvez
utiliser, modifier et/ou redistribuer ce programme sous les conditions
de la licence CeCILL-B telle que diffusée par le CEA, le CNRS et l'INRIA 
sur le site http://www.cecill.info.

En contrepartie de l'accessibilité au code source et des droits de copie,
de modification et de redistribution accordés par cette licence, il n'est
offert aux utilisateurs qu'une garantie limitée.  Pour les mêmes raisons,
seule une responsabilité restreinte pèse sur l'auteur du programme,  le
titulaire des droits patrimoniaux et les concédants successifs.

A cet égard  l'attention de l'utilisateur est attirée sur les risques
associés au chargement,  à l'utilisation,  à la modification et/ou au
développement et à la reproduction du logiciel par l'utilisateur étant 
donné sa spécificité de logiciel libre, qui peut le rendre complexe à 
manipuler et qui le réserve donc à des développeurs et des professionnels
avertis possédant  des  connaissances  informatiques approfondies.  Les
utilisateurs sont donc invités à charger  et  tester  l'adéquation  du
logiciel à leurs besoins dans des conditions permettant d'assurer la
sécurité de leurs systèmes et ou de leurs données et, plus généralement, 
à l'utiliser et l'exploiter dans les mêmes conditions de sécurité. 

Le fait que vous puissiez accéder à cet en-tête signifie que vous avez 
pris connaissance de la licence CeCILL-B, et que vous en avez accepté les
termes.
-----------------------------------------------------------------------*/
#pragma once

#include "resqml2_0/AbstractFeatureInterpretation.h"

namespace resqml2_0
{
	class DLL_IMPORT_OR_EXPORT WellboreInterpretation : public AbstractFeatureInterpretation
	{
	public:
		/**
		* Creates an instance of this class in a gsoap context.
		* @param horizon	The feature the instance interprets.
		* @param guid		The guid to set to the fault. If empty then a new guid will be generated.
		* @param title		A title for the instance to create.
		* @param isDrilled	Indicate if the wellbore is interpreted wether as drilled or not.
		*/
		WellboreInterpretation(class WellboreFeature * WellboreFeature, const std::string & guid, const std::string & title, bool isDrilled);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		WellboreInterpretation(gsoap_resqml2_0::_resqml2__WellboreInterpretation* fromGsoap): AbstractFeatureInterpretation(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~WellboreInterpretation() {}

		/**
		* Indicates if the wellbore has been interpreted as drilled or not.
		*/
		bool isDrilled() const;

		static const char* XML_TAG;
		virtual std::string getXmlTag() const {return XML_TAG;}
	};
}
