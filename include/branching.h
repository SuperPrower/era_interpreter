#ifndef ERA_BRANCHING_H
#define ERA_BRANCHING_H

#include "era_interpreter.h"

#define BRANCH_ERROR_WRONG_REGISTER 1
#define BRANCH_ERROR_WRONG_FORMAT 2

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
int cnd(struct era_t *era, sword_t i, sword_t j, enum format_t format);

/**
 * @brief if Ri goto Rj
 * Checks Ri and if it is non-zero, then the current PC is stored into Pi and sets PC to Rj
 *
 * @param[in] era - pointer to era structure
 * @param[in] i	- no. of register
 * @param[in] j	- no. of register
 * @param[in] format - operation format, F_32_BIT required
 *
 * @returns 0 on success, error code "MEMORY_ERROR_*" on error
 */
int cbr(struct era_t *era, sword_t i, sword_t j, enum format_t format);

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
int nop(struct era_t *era, sword_t i, sword_t j, enum format_t format);

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
int stop(struct era_t *era, sword_t i, sword_t j, enum format_t format);

#endif //ERA_BRANCHING_H
