#ifndef ERRIC_BRANCH_OPERATORS_H
#define ERRIC_BRANCH_OPERATORS_H

#include "erric_interpreter.h"

/**
 * @brief Rj ?= Ri
 * Compares Rj and Ri and puts the results of comparison into 4 lowest bits of Rj
 *
 * @param[in] erric - pointer to erric structure
 * @param[in] i	- no. of register
 * @param[in] j	- no. of register
 * @param[in] format - operation format
 *
 * @returns ERRIC_STATUS_NONE on success, appropriate ERRIC_STATUS_* on error
 */
sword_t cnd(struct erric_t *erric, sword_t i, sword_t j, enum format_t format);

/**
 * @brief if Ri goto Rj
 * Checks Ri and if it is non-zero, then the current PC is stored into Ri and sets PC to Rj
 *
 * @param[in] erric - pointer to erric structure
 * @param[in] i	- no. of register
 * @param[in] j	- no. of register
 * @param[in] format - operation format, F_32_BIT required
 *
 * @returns ERRIC_STATUS_NONE on success, appropriate ERRIC_STATUS_* on error
 */
sword_t cbr(struct erric_t * erric, sword_t i, sword_t j, enum format_t format);

/**
 * @brief does nothing
 *
 * @param[in] erric - pointer to erric structure
 * @param[in] i	- no. of register
 * @param[in] j	- no. of register
 * @param[in] format - operation format, F_16_BIT required
 *
 * @returns ERRIC_STATUS_NONE on success, appropriate ERRIC_STATUS_* on error
 */
sword_t nop(struct erric_t * erric, sword_t i, sword_t j, enum format_t format);

/**
 * @brief stops the execution
 *
 * @param[in] erric - pointer to erric structure
 * @param[in] i	- no. of register
 * @param[in] j	- no. of register
 * @param[in] format - operation format, F_8_BIT required
 *
 * @returns ERRIC_STATUS_NONE on success, appropriate ERRIC_STATUS_* on error
 */
sword_t stop(struct erric_t *erric, sword_t i, sword_t j, enum format_t format);

// Utility function for the execution table
sword_t nopstop(struct erric_t *erric, sword_t i, sword_t j, enum format_t format);

#endif //ERRIC_BRANCH_OPERATORS_H
