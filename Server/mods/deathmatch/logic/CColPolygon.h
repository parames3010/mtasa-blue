/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        mods/deathmatch/logic/CColPolygon.h
 *  PURPOSE:     Polygon-shaped collision entity class
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/

#pragma once

#include "CColShape.h"

#include <list>

class CColPolygon : public CColShape
{
public:
    CColPolygon(CColManager* pManager, CElement* pParent, const CVector& vecPosition);
    CElement* Clone(bool* bAddEntity, CResource* pResource) override;

    virtual CSphere GetWorldBoundingSphere();

    eColShapeType GetShapeType() { return COLSHAPE_POLYGON; }

    bool DoHitDetection(const CVector& vecNowPosition);

    void SetPosition(const CVector& vecPosition);

    void AddPoint(CVector2D vecPoint);

    unsigned int                           CountPoints() const { return static_cast<unsigned int>(m_Points.size()); };
    std::vector<CVector2D>::const_iterator IterBegin() { return m_Points.begin(); };
    std::vector<CVector2D>::const_iterator IterEnd() { return m_Points.end(); };

protected:
    std::vector<CVector2D> m_Points;

    bool ReadSpecialData(const int iLine) override;

    bool IsInBounds(CVector vecPoint);

    float m_fRadius;
};
