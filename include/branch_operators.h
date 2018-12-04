#ifndef ERA_BRANCH_OPERATORS_H
#define ERA_BRANCH_OPERATORS_H

#include "era_interpreter.h"

/**
 * @brief Rj ?= Ri
 * Compares Rj and Ri and puts the results of comparison into 4 lowest bits of Rj
 *
 * @param[in] era - pointer to era structure
 * @param[in] i	- no. of register
 * @param[in] j	- no. of register
 * @param[in] format - operation format
 *
 * @returns 0 on success, error code "MEMORY_ERROR_*" on error
 */
sword_t cnd(struct era_t *era, sword_t i, sword_t j, enum format_t format);

/**
 * @brief if Ri goto Rj
 * Checks Ri and if it is non-zero, then the current PC is stored into Ri and sets PC to Rj
 *
 * @param[in] era - pointer to era structure
 * @param[in] i	- no. of register
 * @param[in] j	- no. of register
 * @param[in] format - operation format, F_32_BIT required
 *
 * @returns 0 on success, error code "MEMORY_ERROR_*" on error
 */
sword_t cbr(struct era_t * era, sword_t i, sword_t j, enum format_t format);

/**
 * @brief does nothing
 *
 * @param[in] era - pointer to era structure
 * @param[in] i	- no. of register
 * @param[in] j	- no. of register
 * @param[in] format - operation format, F_16_BIT required
 *
 * @returns 0 on success, error code "MEMORY_ERROR_*" on error
 */
sword_t nop(struct era_t * era, sword_t i, sword_t j, enum format_t format);

/**
 * @brief stops the execution
 *
 * @param[in] era - pointer to era structure
 * @param[in] i	- no. of register
 * @param[in] j	- no. of register
 * @param[in] format - operation format, F_8_BIT required
 *
 * @returns 0 on success, error code "MEMORY_ERROR_*" on error
 */
sword_t stop(struct era_t *era, sword_t i, sword_t j, enum format_t format);

// Utility function for the execution table
sword_t nopstop(struct era_t *era, sword_t i, sword_t j, enum format_t format);

#endif //ERA_BRANCH_OPERATORS_H
