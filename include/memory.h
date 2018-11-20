#ifndef ERA_MEMORY_H
#define ERA_MEMORY_H

#include "era_interpreter.h"

#define MEMORY_ERROR_OUT_OF_BOUNDS 1
#define MEMORY_ERROR_WRONG_FORMAT 2
#define MEMORY_ERROR_WRONG_REGISTER 3

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
int ld(struct era_t *era, sword_t i, sword_t j, enum format_t format);

/**
 * @brief Rj = Ri + constant
 * Takes the value from the next in-memory 32-bit word, adds it with the value of Ri, then stores into Rj
 * Side-effects: PC is updated and increased by 1, with the assumption that the function is called from a loop and PC
 *  will be incremented by 1 after calling this one
 *
 * @param[in] era - pointer to era structure
 * @param[in] i	- no. of register
 * @param[in] j	- no. of register
 * @param[in] format - operation format, F_32_BIT required
 *
 * @returns 0 on success, error code "MEMORY_ERROR_*" on error
 */
int lda(struct era_t *era, sword_t i, sword_t j, enum format_t format);

/**
 * @brief Rj = constant
 * Put the value of a constant inside the command into Rj register
 *
 * @param[in] era - pointer to era structure
 * @param[in] i	- constant
 * @param[in] j	- no. of register
 * @param[in] format - operation format, F_32_BIT required
 *
 * @returns 0 on success, error code "MEMORY_ERROR_*" on error
 */
int ldc(struct era_t *era, sword_t i, sword_t j, enum format_t format);

/**
 * @brief *Rj = Ri
 * Put the value from Ri register into memory pointed to by Rj register
 *
 * @param[in] era - pointer to era structure
 * @param[in] i	- no. of register
 * @param[in] j	- no. of register
 * @param[in] format - operation format, F_32_BIT required
 *
 * @returns 0 on success, error code "MEMORY_ERROR_*" on error
 */
int st(struct era_t *era, sword_t i, sword_t j, enum format_t format);

/**
 * @brief Rj = Ri
 * Copy Ri into Rj
 *
 * @param[in] era - pointer to era structure
 * @param[in] i	- no. of register
 * @param[in] j	- no. of register
 * @param[in] format - operation format, F_32_BIT required
 *
 * @returns 0 on success, error code "MEMORY_ERROR_*" on error
 */
int mov(struct era_t *era, sword_t i, sword_t j, enum format_t format);

#endif //ERA_MEMORY_H