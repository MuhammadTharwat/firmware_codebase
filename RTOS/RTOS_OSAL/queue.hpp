/**
  ******************************************************************************
  * @file			queue.hpp
  * @description	Queue class interface
  * @author			Muhammad Tharwat
  * @version		V0.0
  * @date			19-August-2024
  ******************************************************************************
*/

#ifndef QUEUE_H_
#define QUEUE_H_

#include <noncopyable.hpp>
#include <rtos_imp.hpp>
#include <rtos_err.hpp>
#include <cstdint>
/***********************************************  Defines    **************************************************/


/***********************************************  Constants   *************************************************/

/***********************************************  Enumerations   **********************************************/

/*********************************************** Data types  **************************************************/
namespace rtos_osal
{
	class queue : private noncopyable
	{
	public:
		/**
		 * @brief Create a message queue
		 *
		 * This is the function used to create a queue in the operating system.
		 * Depending on the underlying operating system, the memory for the queue
		 * will be allocated automatically.
		 * Queue names must be unique; if the name already exists this
		 * function fails. Names cannot be NULL.
		 *
		 * @param[in]   QueueName the name of the new queue to create
		 * @param[in]   QueueDepth the maximum depth of the queue
		 * @param[in]   QuaueEntrySize the size of each entry in the queue
		 * @param[in]   QueueMemory queue memory buffer (Must be >= QueueDepth * QuaueEntrySize) 
		 * 							or NULL for Dynamic allocation
		 * */
		explicit queue(const char *, std::uint32_t, std::size_t, void *);

		~queue(void) = default;

		/**
		 * @brief Receive a message on a message queue
		 *
		 * If a message is pending, it is returned immediately.  Otherwise the calling task
		 * will block until a message arrives or the timeout expires.
		 *
		 * @param[out]  QueueDataBuffer The buffer to store the received message
		 * @param[in]   QueuedataBufferSize The size of the data buffer
		 * @param[in]   QueueTimeout The maximum amount of time to block
		 * 
		 * @return Execution status, see @ref tenu_osal_status
		 */
		tenu_osal_status receive(void *, std::size_t, std::uint32_t);

		/**
		 * @brief Receive a message on a message queue from ISR
		 *
		 * If a message is pending, it is returned immediately
		 *
		 * @param[out]  QueueDataBuffer The buffer to store the received message
		 * @param[in]   QueuedataBufferSize The size of the data buffer
		 * 
		 * @return Execution status, see @ref tenu_osal_status
		 */

		tenu_osal_status receive_from_isr(void *, std::size_t);

		/**
		 * @brief Put a message on a message queue
		 *
		 * If a message is pending, it is returned immediately.  Otherwise the calling task
		 * will block until a message arrives or the timeout expires.
		 *
		 * @param[in]  QueueDataBuffer The buffer to store the received message
		 * @param[in]  QueueDataBufferSize The size of the data buffer
		 * @param[in]   QueueTimeout The maximum amount of time to block
		 * 
		 * @return Execution status, see @ref tenu_osal_status
		 */
		tenu_osal_status send(const void *, std::size_t, std::uint32_t);

		/**
		 * @brief Put a message on a message queue
		 *
		 * If a message is pending, it is sent immediately
		 *
		 * @param[in]  QueueDataBuffer The buffer to store the message to send
		 * @param[in]  QueueDataBufferSize The size of the data buffer
		 * 
		 * @return Execution status, see @ref tenu_osal_status
		 */

		tenu_osal_status send_from_isr(const void *, std::size_t);

		/**
		 * @brief Get queue ID
		 * 
		 * @return Queue ID
		 */
		std::uint32_t get_id(void);

		/**
		 * @brief Delete Queue
		 * 
		 * @return Execution status, see @ref tenu_osal_status
		 */
		tenu_osal_status del(void);
	private:
		queue_mem str_queue_mem;
	};
}
#endif /* QUEUE_H_ */
