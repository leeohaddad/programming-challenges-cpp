/***************************************************************/
/**                                                           **/
/**   Leonardo Haddad                           nº 7295361    **/
/**   Desafios de Programação - Round 3    Professora Cris    **/
/**   Problema 2 - Divide an Island!            Curso: BCC    **/
/**                                                           **/
/***************************************************************/

#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define MAX_DIST 6000
#define debug_off 1
#define error 1e-9

using namespace std;

int xA, yA, xB, yB, xC, yC;
int xAtoB, yAtoB, xBtoC, yBtoC, xCtoA, yCtoA;
double abLength, bcLength, caLength, fullLength, abPercentage, bcPercentage, caPercentage;
double totalArea;

#ifdef debug_on
/* print arguments */
void printArgs () {
	printf("Arguments:\n");
	printf(" A = %d %d;\n",xA,yA);
	printf(" B = %d %d;\n",xB,yB);
	printf(" C = %d %d;\n",xC,yC);
}
#endif

double normalizedToX (double normalizedValue)
{
	if (normalizedValue < abPercentage)
	{
		return xA + xAtoB * (normalizedValue / abPercentage);
	}
	else if (normalizedValue < abPercentage + bcPercentage)
	{
		return xB + xBtoC * ((normalizedValue - abPercentage) / bcPercentage);
	}
	else
	{
		return xC + xCtoA * ((normalizedValue - abPercentage - bcPercentage) / caPercentage);
	}
}

double normalizedToY (double normalizedValue)
{
	if (normalizedValue < abPercentage)
	{
		return yA + yAtoB * (normalizedValue / abPercentage);
	}
	else if (normalizedValue < abPercentage + bcPercentage)
	{
		return yB + yBtoC * ((normalizedValue - abPercentage) / bcPercentage);
	}
	else
	{
		return yC + yCtoA * ((normalizedValue - abPercentage - bcPercentage) / caPercentage);
	}
}

double areaFromPointsViaHeronFormula (double pxA, double pyA, double pxB, double pyB, double pxC, double pyC)
{
	double abL = sqrt((pxB-pxA)*(pxB-pxA)+(pyB-pyA)*(pyB-pyA));
	double bcL = sqrt((pxC-pxB)*(pxC-pxB)+(pyC-pyB)*(pyC-pyB));
	double caL = sqrt((pxA-pxC)*(pxA-pxC)+(pyA-pyC)*(pyA-pyC));
	double semiPer = (abL + bcL + caL) / 2;
	return sqrt(semiPer * (semiPer - abL) * (semiPer - bcL) * (semiPer - caL));
}

double areaFromPointsViaCrossProduct (double pxA, double pyA, double pxB, double pyB, double pxC, double pyC)
{
	double abL = sqrt((pxB-pxA)*(pxB-pxA)+(pyB-pyA)*(pyB-pyA));
	double bcL = sqrt((pxC-pxB)*(pxC-pxB)+(pyC-pyB)*(pyC-pyB));
	double caL = sqrt((pxA-pxC)*(pxA-pxC)+(pyA-pyC)*(pyA-pyC));
	double angle = acos((abL*abL+caL*caL-bcL*bcL) / (2*abL*caL));
	return (0.5 * abL * caL * sin(angle)); 
}

double areaFromPoints (double pxA, double pyA, double pxB, double pyB, double pxC, double pyC)
{
	//return areaFromPointsViaHeronFormula(pxA,pyA,pxB,pyB,pxC,pyC);
	return areaFromPointsViaCrossProduct(pxA,pyA,pxB,pyB,pxC,pyC);
}

double normalizedToArea (double normalizedValue)
{
	double otherEdge = normalizedValue + 0.5;
	if (otherEdge > 1.0)
		otherEdge = otherEdge - 1.0;
	if (normalizedValue == 0)
	{
		return areaFromPoints(xB,yB,normalizedToX(normalizedValue),normalizedToY(normalizedValue),normalizedToX(otherEdge),normalizedToY(otherEdge));	
	}
	else if (normalizedValue < abPercentage)
	{
		if (otherEdge < abPercentage+bcPercentage)
		{
			return areaFromPoints(xB,yB,normalizedToX(normalizedValue),normalizedToY(normalizedValue),normalizedToX(otherEdge),normalizedToY(otherEdge));
		}
		else
		if (otherEdge <= abPercentage+bcPercentage+caPercentage)
		{
			return areaFromPoints(xA,yA,normalizedToX(normalizedValue),normalizedToY(normalizedValue),normalizedToX(otherEdge),normalizedToY(otherEdge));
		}
		else
			printf("error (if1)!\n");
	}
	else if (normalizedValue == abPercentage)
	{
		return areaFromPoints(xC,yC,normalizedToX(normalizedValue),normalizedToY(normalizedValue),normalizedToX(otherEdge),normalizedToY(otherEdge));	
	}
	else if (normalizedValue < abPercentage+bcPercentage)
	{
		if (otherEdge < abPercentage)
		{
			return areaFromPoints(xB,yB,normalizedToX(normalizedValue),normalizedToY(normalizedValue),normalizedToX(otherEdge),normalizedToY(otherEdge));
		}
		else
		if (otherEdge <= abPercentage+bcPercentage+caPercentage)
		{
			return areaFromPoints(xC,yC,normalizedToX(normalizedValue),normalizedToY(normalizedValue),normalizedToX(otherEdge),normalizedToY(otherEdge));
		}	
		else
			printf("error (if2)!\n");
	}
	else if (normalizedValue == abPercentage+bcPercentage)
	{
		return areaFromPoints(xA,yA,normalizedToX(normalizedValue),normalizedToY(normalizedValue),normalizedToX(otherEdge),normalizedToY(otherEdge));	
	}
	else if (normalizedValue < abPercentage+bcPercentage+caPercentage)
	{
		if (otherEdge < abPercentage)
		{
			return areaFromPoints(xA,yA,normalizedToX(normalizedValue),normalizedToY(normalizedValue),normalizedToX(otherEdge),normalizedToY(otherEdge));
		}
		else
		if (otherEdge < abPercentage+bcPercentage)
		{
			return areaFromPoints(xC,yC,normalizedToX(normalizedValue),normalizedToY(normalizedValue),normalizedToX(otherEdge),normalizedToY(otherEdge));
		}
		else
			printf("error (if3)!\n");
	}
	else if (normalizedValue == abPercentage+bcPercentage+caPercentage)
	{
		return areaFromPoints(xB,yB,normalizedToX(normalizedValue),normalizedToY(normalizedValue),normalizedToX(otherEdge),normalizedToY(otherEdge));	
	}
	else
		printf("error (final)!\n");
	return -1;
}

void bruteForceSolution () {
	int precision;
	double attempt, dist, from, to, area, normalizedValueA, normalizedValueB;
	totalArea = areaFromPoints(xA,yA,xB,yB,xC,yC);
	#ifdef debug_on
		printf("  totalArea: %.15f\n",totalArea);
	#endif
	dist = MAX_DIST;
	normalizedValueA = -1;
	precision = 4;
	from = 0;
	to = 0.5;
	while (precision < 15)
	{
		attempt = from;
		while (attempt < to)
		{
			area = normalizedToArea(attempt);
			if (abs(area - totalArea/2) < dist)
			{	
				dist = abs(area - totalArea/2);
				normalizedValueA = attempt;
			}
			#ifdef debug_on
				printf("  %.15f: (%.2f %.2f) ; area = %.15f\n",attempt,normalizedToX(attempt),normalizedToY(attempt),area);
			#endif
			attempt = attempt + pow(10,-precision);
		}
		from = normalizedValueA - pow(10,-precision);
		to = normalizedValueA + pow(10,-precision);
		if (from < 0)
			from = 0;
		if (to > 0.5)
			to = 0.5;
		precision++;
	}
	normalizedValueB = normalizedValueA + 0.5;
	if (normalizedValueB >= 1.0)
		normalizedValueB = normalizedValueB - 1.0;
	if (dist < error)
		printf("YES\n%.15f %.15f\n%.15f %.15f\n", normalizedToX(normalizedValueA), normalizedToY(normalizedValueA), normalizedToX(normalizedValueB), normalizedToY(normalizedValueB));
	else
		printf("NO\n");
}

int main () {
	double semiPerimeter, linearFactorA, linearFactorB, ansXa, ansYa, ansXb, ansYb;
	bool finished;

	#ifdef debug_on
		printf("\n| P2 - Divide an Island! |\n");
	#endif

    /* read program arguments */
	scanf("%d %d %d %d %d %d", &xA, &yA, &xB, &yB, &xC, &yC);

	#ifdef debug_on
		printArgs();
		printf("\nProblem Solution:\n");
	#endif

	/* solution */
	xAtoB = xB - xA;
	yAtoB = yB - yA;
	xBtoC = xC - xB;
	yBtoC = yC - yB;
	xCtoA = xA - xC;
	yCtoA = yA - yC;
	abLength = sqrt(xAtoB*xAtoB + yAtoB*yAtoB);
	bcLength = sqrt(xBtoC*xBtoC + yBtoC*yBtoC);
	caLength = sqrt(xCtoA*xCtoA + yCtoA*yCtoA);
	fullLength = abLength + bcLength + caLength;
	semiPerimeter = fullLength / 2;
	abPercentage = abLength / fullLength;
	bcPercentage = bcLength / fullLength;
	caPercentage = caLength / fullLength;
	//bruteForceSolution();
	finished = false;
	linearFactorA = (semiPerimeter - sqrt(semiPerimeter * semiPerimeter - 2 * abLength * bcLength)) / 2;
	linearFactorB = (semiPerimeter + sqrt(semiPerimeter * semiPerimeter - 2 * abLength * bcLength)) / 2;
   if(linearFactorA <= abLength + error && linearFactorB <= bcLength + error) {
   	ansXa = xB - xAtoB * (linearFactorA / abLength);
   	ansYa = yB - yAtoB * (linearFactorA / abLength);
   	ansXb = xB + xBtoC * (linearFactorB / bcLength);
   	ansYb = yB + yBtoC * (linearFactorB / bcLength);
   	printf("YES\n%.15f %.15f\n%.15f %.15f\n", ansXa, ansYa, ansXb, ansYb);
   	finished = true;
	}
   if(!finished && linearFactorB <= abLength + error && linearFactorA <= bcLength + error) {
   	ansXa = xB - xAtoB * (linearFactorB / abLength);
   	ansYa = yB - yAtoB * (linearFactorB / abLength);
   	ansXb = xB + xBtoC * (linearFactorA / bcLength);
   	ansYb = yB + yBtoC * (linearFactorA / bcLength);
   	printf("YES\n%.15f %.15f\n%.15f %.15f\n", ansXa, ansYa, ansXb, ansYb);
   	finished = true;
   }
	linearFactorA = (semiPerimeter - sqrt(semiPerimeter * semiPerimeter - 2 * bcLength * caLength)) / 2;
	linearFactorB = (semiPerimeter + sqrt(semiPerimeter * semiPerimeter - 2 * bcLength * caLength)) / 2;
   if(!finished && linearFactorA <= bcLength + error && linearFactorB <= caLength + error) {
   	ansXa = xC - xBtoC * (linearFactorA / bcLength);
   	ansYa = yC - yBtoC * (linearFactorA / bcLength);
   	ansXb = xC + xCtoA * (linearFactorB / caLength);
   	ansYb = yC + yCtoA * (linearFactorB / caLength);
   	printf("YES\n%.15f %.15f\n%.15f %.15f\n", ansXa, ansYa, ansXb, ansYb);
   	finished = true;
	}
   if(!finished && linearFactorB <= bcLength + error && linearFactorA <= caLength + error) {
   	ansXa = xC - xBtoC * (linearFactorB / bcLength);
   	ansYa = yC - yBtoC * (linearFactorB / bcLength);
   	ansXb = xC + xCtoA * (linearFactorA / caLength);
   	ansYb = yC + yCtoA * (linearFactorA / caLength);
   	printf("YES\n%.15f %.15f\n%.15f %.15f\n", ansXa, ansYa, ansXb, ansYb);
   	finished = true;
   }
	linearFactorA = (semiPerimeter - sqrt(semiPerimeter * semiPerimeter - 2 * caLength * abLength)) / 2;
	linearFactorB = (semiPerimeter + sqrt(semiPerimeter * semiPerimeter - 2 * caLength * abLength)) / 2;
   if(!finished && linearFactorA <= caLength + error && linearFactorB <= abLength + error) {
   	ansXa = xA - xCtoA * (linearFactorA / caLength);
   	ansYa = yA - yCtoA * (linearFactorA / caLength);
   	ansXb = xA + xAtoB * (linearFactorB / abLength);
   	ansYb = yA + yAtoB * (linearFactorB / abLength);
   	printf("YES\n%.15f %.15f\n%.15f %.15f\n", ansXa, ansYa, ansXb, ansYb);
   	finished = true;
	}
   if(!finished && linearFactorB <= caLength + error && linearFactorA <= abLength + error) {
   	ansXa = xA - xCtoA * (linearFactorB / caLength);
   	ansYa = yA - yCtoA * (linearFactorB / caLength);
   	ansXb = xA + xAtoB * (linearFactorA / abLength);
   	ansYb = yA + yAtoB * (linearFactorA / abLength);
   	printf("YES\n%.15f %.15f\n%.15f %.15f\n", ansXa, ansYa, ansXb, ansYb);
   	finished = true;
   }
   if (!finished)
   {
   	printf("NO\n");
   }

	#ifdef debug_on
		printf("\n--------------------\n");
	#endif
	return 0;
}

/*

1647. Divide an Island!
Time limit: 1.0 second
Memory limit: 64 MB
Url: http://acm.timus.ru/problem.aspx?space=1&num=1647

A desert island Robinson Crusoe and his companion Friday live on has a shape of a non-degenerate triangle which vertices are points (x1, y1), (x2, y2), (x3, y3). Once Robinson and Friday fell aboard and decided to divide the island into two equal parts by choosing two points on the island coast and connecting them with a line segment. These parts were to have the same area and shore length. Robinson failed to choose these points. Can you do it for him?

Input:
The only line of the input contains space-separated integers x1, y1, x2, y2, x3, y3, not exceeding 2000 in absolute value.

Output:
If there is a line segment ST, which divides the island into two parts of the same area and shore length, output “YES” on the first line of the output, S coordinates on the second line, and T coordinates of the third line. S and T should be located on the island shore. Coordinates should be accurate within 10−9. If there is no such line segment, output “NO” on a single line.

Samples:

Input:
0 0 10 0 0 10
Output:
YES
0 0
5 5

Input:
0 3 4 0 3 4
Output:
YES
1.741248277008306 3.580416092336102
3.445803840397070 0.415647119702198

*/
