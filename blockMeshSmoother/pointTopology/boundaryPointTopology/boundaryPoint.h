/*---------------------------------------------------------------------------*\
  extBlockMesh
  Copyright (C) 2014 Etudes-NG
  ---------------------------------
License
    This file is part of extBlockMesh.

    extBlockMesh is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    extBlockMesh is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with extBlockMesh.  If not, see <http://www.gnu.org/licenses/>.

\*---------------------------------------------------------------------------*/

#ifndef BOUNDARYPOINT_H
#define BOUNDARYPOINT_H

#include "pointTopo.h"

#include <set>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
             Class boundaryPoint Declaration
\*---------------------------------------------------------------------------*/

class boundaryPoint : public pointTopo
{
    //- Private data

protected:

    //- Protected data

        //- Triangles faces connected to this point at beginning
        std::set<std::set<label> > triangles_;

        //- Triangles faces connected to this point during smoothing
        std::set<std::set<label> > trianglesNew_;

        //- Initial point
        point initialPoint_;

        //- initial point label
        label initialPointLabel_;

        //- Point label during smoothing
        label newPointLabel_;


    //- Protected member functions

        //- Test triangle
        bool isOnTriangle
        (
            const label &refP2,
            const label &refP3,
            const point &p,
            point &out
        ) const;

        //- Change feature edge linked points and get optimal point
        virtual point changeFeatureEdgeLinkedsPoint
        (
            const label &newRef,
            const point &guessedPoint
        );

        //- Change boundary linked faces and get optimal point
        point changeBoundaryPointLinkedFaces
        (
            const label &newRef,
            const point &guessedPoint
        );

        //- Initial boundary point
        point getInitialPoint(const label &ref) const;

public:
    //- Constructors

        //- Construct from
        boundaryPoint
        (
            const std::set<std::set<Foam::label> > &triangles,
            const point &initialPoint,
            const label &initialLabel,
            blockMeshTopology *topo
        );

    //- Destructor
        ~boundaryPoint();

    //- Member functions

        //- get optimal point with repect of point topo
        point smoothedPoint(const point &guessedPoint);

        //- Get map of neibor features edge points sorted by minimal distance
        std::map<scalar,point> mapNeiborFeaturePts
        (
            const point &guessedPoint
        ) const;

        //- Get map of neibor boundary points sorted by minimal distance
        std::map<scalar,point> mapBoundaryFeaturePts
        (
            const point &guessedPoint
        );

        //- Get optimal boundary point from guessed
        point projectedBndPoint(const point &guessedPoint);


        //- Get optimal point from guessed
        virtual point getFeatureEdgePoint
        (
            const point &guessedPoint,
            const label &ref
        );

        //- Get triangles linked
        std::set<std::set<label> > getTrianglesLinked() const;

        //- Get boundaryPoint coord
        point &getboundaryPoint();
};

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // BOUNDARYPOINT_H

// ************************************************************************* //

