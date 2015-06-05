/*!
 * \file
 * \brief Поток для пула асинхронных задач
 */

#ifndef _ekstertera_thread_h_
#define _ekstertera_thread_h_

#include "queue.h"

/*!
 * \brief Поток для пула асинхронных задач
 */
class EteraThread : public QThread
{
    Q_OBJECT

    public:

        /*!
         * \brief Конструктор
         * \param queue Общая очередь задач
         * \param wait Блокировка на появление новой задачи
         * \param destiny Предпочитаемый приоритет задач
         */
        EteraThread(EteraTaskQueue* queue, QWaitCondition* wait, EteraTaskPriority destiny = etpIdle);
        ~EteraThread();

        /*!
         * \brief Остановка разбора очереди задач
         */
        void stop() { m_stopped = true; }

        /*!
         * \brief Предпочитаемый приоритет задач
         * \return Предпочитаемый приоритет задач
         */
        EteraTaskPriority destiny() const { return m_destiny; }

    protected:

        // QThread::run
        void run();

    private:

        bool              m_stopped;   /*!< \brief Флаг необходимости завершения работы */
        QMutex            m_mutex;     /*!< \brief Блокировка для m_wait                */
        EteraTaskQueue*   m_queue;     /*!< \brief Очередь задач                        */
        QWaitCondition*   m_wait;      /*!< \brief Блокировка на появление новой задачи */
        EteraTaskPriority m_destiny;   /*!< \brief Предпочитаемый приоритет задач       */
};

/*!
 * \brief Список потоков для пула асинхронных задач
 */
typedef QList<EteraThread*> EteraThreadList;

#endif   // _ekstertera_thread_h_