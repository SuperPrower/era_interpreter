#ifndef ERRIC_MATH_OPERATORS_H
#define ERRIC_MATH_OPERATORS_H

#include "erric_interpreter.h"

/**
 * @brief Rj += Ri
 * Add content of registers i and j and store result in register j
 *
 * @param[in] erric - pointer to erric structure
 * @param[in] i	- no. of register
 * @param[in] j	- no. of register
 * @param[in] format - operation format
 *
 * @returns ERRIC_STATUS_NONE on success
 */
sword_t add(struct erric_t *erric, sword_t i, sword_t j, enum format_t format);

/**
 * @brief Rj -= Ri
 * Subtract content of registers i from register j and store result in register j
 *
 * @param[in] erric - pointer to erric structure
 * @param[in] i	- no. of register
 * @param[in] j	- no. of register
 * @param[in] format - operation format
 *
 * @returns ERRIC_STATUS_NONE on success
 */
sword_t sub(struct erric_t *erric, sword_t i, sword_t j, enum format_t format);

/**
 * @brief Rj = Ri >> 1
 * Arithmetically (preserving sign) shift contents of register i one bit right
 * and store result into register j
 *
 * @param[in] erric - pointer to erric structure
 * @param[in] i	- no. of register
 * @param[in] j	- no. of register
 * @param[in] format - operation format
 *
 * @returns ERRIC_STATUS_NONE on success
 */
sword_t asr(struct erric_t *erric, sword_t i, sword_t j, enum format_t format);

/**
 * @brief Rj = Ri << 1
 * Arithmetically (preserving sign) shift contents of register i one bit left
 * and store result into register j
 *
 * @param[in] erric - pointer to erric structure
 * @param[in] i	- no. of register
 * @param[in] j	- no. of register
 * @param[in] format - operation format
 *
 * @returns ERRIC_STATUS_NONE on success
 */
sword_t asl(struct erric_t *erric, sword_t i, sword_t j, enum format_t format);

#endif /* ifndef ERRIC_MATH_OPERATORS_H */
