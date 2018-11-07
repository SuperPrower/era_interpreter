#ifndef ERA_MEMORY_H
#define ERA_MEMORY_H

#include "era_interpreter.h"

#define MEMORY_ERROR_OUT_OF_BOUNDS 1
#define MEMORY_ERROR_WRONG_FORMAT 2

/**
 * @brief Rj = *Ri
 * Load contents from memory address in Ri to Rj
 *
 * @param[in] era - pointer to era structure
 * @param[in] i	- no. of register
 * @param[in] j	- no. of register
 * @param[in] format - operation format, F_32_BIT required
 *
 * @returns 0 on success, error code "MEMORY_ERROR_*" on error
 */
int ld(struct era_t *era, uint8_t i, uint8_t j, enum format_t format);

/**
 * @brief Rj = Ri + constant
 * Takes the value from the next in-memory 32-bit word, adds it with the value of Ri, then stores into Rj
 *
 * @param[in] era - pointer to era structure
 * @param[in] i	- no. of register
 * @param[in] j	- no. of register
 * @param[in] format - operation format, F_32_BIT required
 *
 * @returns 0 on success, error code "MEMORY_ERROR_*" on error
 */
int lda(struct era_t *era, uint8_t i, uint8_t j, enum format_t format);

/**
 * @brief Rj = *Ri
 * Load contents from memory address in Ri to Rj
 *
 * @param[in] era - pointer to era structure
 * @param[in] i	- no. of register
 * @param[in] j	- no. of register
 * @param[in] format - operation format, F_32_BIT required
 *
 * @returns 0 on success, error code "MEMORY_ERROR_*" on error
 */
int ldc(struct era_t *era, uint8_t i, uint8_t j, enum format_t format);

/**
 * @brief Rj = Ri + constant
 * Fill in
 *
 * @param[in] era - pointer to era structure
 * @param[in] i	- no. of register
 * @param[in] j	- no. of register
 * @param[in] format - operation format, F_32_BIT required
 *
 * @returns 0 on success, error code "MEMORY_ERROR_*" on error
 */
int st(struct era_t *era, uint8_t i, uint8_t j, enum format_t format);

/**
 * @brief Rj = *Ri
 * Load contents from memory address in Ri to Rj
 *
 * @param[in] era - pointer to era structure
 * @param[in] i	- no. of register
 * @param[in] j	- no. of register
 * @param[in] format - operation format, F_32_BIT required
 *
 * @returns 0 on success, error code "MEMORY_ERROR_*" on error
 */
int mov(struct era_t *era, uint8_t i, uint8_t j, enum format_t format);

#endif //ERA_MEMORY_H
