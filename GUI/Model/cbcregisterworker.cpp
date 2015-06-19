#pragma once
#include "cbcregisterworker.h"
#include <QDebug>
#include <QThread>


using namespace Ph2_HwDescription;
using namespace Ph2_HwInterface;

namespace GUI
{
    CbcRegisterWorker::CbcRegisterWorker(QObject *parent,
                                         SystemController &sysCtrl) :
        QObject(parent),
        m_systemController(sysCtrl)
    {
    }
    CbcRegisterWorker::~CbcRegisterWorker()
    {
        qDebug() << "Destructing CbcRegister Worker" << this;
    }

    void CbcRegisterWorker::requestWork()
    {
        qDebug()<<"Request worker start in Thread "<<thread()->currentThreadId();
        emit workRequested();
    }

    void CbcRegisterWorker::abort()
    {
        //TODO
        /*mutex.lock();
        if (_working) {
            _abort = true;
            qDebug()<<"Request worker aborting in Thread "<<thread()->currentThreadId();
        }
        mutex.unlock();*/
    }

    void CbcRegisterWorker::getObjects()
    {
        fBeBoardInterface = m_systemController.getBeBoardInterface();
        fCbcInterface = m_systemController.getCbcInterface();
        fShelveVector = m_systemController.getfShelveVector();
        fBeBoardFWMap = m_systemController.getBeBoardFWMap();
    }

    void CbcRegisterWorker::getInitialCbcRegistersMap()
    {
        getObjects();

        for ( auto cShelve : fShelveVector )
        {
            for ( auto cBoard : ( cShelve )->fBoardVector )
            {
                for ( auto cFe : cBoard->fModuleVector )
                {
                    fCbcInterface->ReadAllCbc(cFe);

                    for ( auto cCbc : cFe->fCbcVector )
                    {
                        emit sendInitialCbcRegisterValues(cShelve->getShelveId(),
                                                          cBoard->getBeId(),
                                                          cFe->getFeId(),
                                                          cCbc->getCbcId(), cCbc->getRegMap());
                    }
                }
            }
        }

        emit finishedInitCbcReg();
    }

    void CbcRegisterWorker::getCbcRegistersMap()
    {
        getObjects();

        for ( auto cShelve : fShelveVector )
        {
            for ( auto cBoard : ( cShelve )->fBoardVector )
            {
                for ( auto cFe : cBoard->fModuleVector )
                {
                    fCbcInterface->ReadAllCbc(cFe);

                    for ( auto cCbc : cFe->fCbcVector )
                    {
                        emit sendCbcRegisterValues(cShelve->getShelveId(),
                                                  cBoard->getBeId(),
                                                  cFe->getFeId(),
                                                  cCbc->getCbcId(), cCbc->getRegMap());
                    }
                }
            }
        }
        emit globalEnable(true);
    }

    void CbcRegisterWorker::writeCbcRegisters(const int idSh, const int idBe, const int idFe, const int idCbc,
                                              std::vector<std::pair<std::string, std::uint8_t>> mapReg)
    {
        getObjects();

        for ( auto cShelve : fShelveVector )
        {
            if (cShelve->getShelveId() == idSh) {
                for ( auto cBoard : ( cShelve )->fBoardVector )
                {
                    if (cBoard->getBeId() == idBe)
                    {
                        for ( auto cFe : cBoard->fModuleVector )
                        {
                            if (cFe->getFeId() == idFe)
                            {
                                for ( auto cCbc : cFe->fCbcVector )
                                {
                                    if (cCbc->getCbcId()==idCbc)
                                    {
                                        fCbcInterface->WriteCbcMultReg(cCbc, mapReg );
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        emit globalEnable(true);
    }

}
