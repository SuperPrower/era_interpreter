#ifndef ERRIC_LOGIC_OPERATORS_H
#define ERRIC_LOGIC_OPERATORS_H

#include "erric_interpreter.h"

/**
 * @brief Rj BITWISE OR Ri
 * Applies the OR operator to every bit of Rj and Ri and stores the result in Rj
 *
 * @param[in] erric - pointer to erric structure
 * @param[in] i	- no. of register
 * @param[in] j	- no. of register
 * @param[in] format - operation format
 *
 * @returns ERRIC_STATUS_NONE on success, appropriate ERRIC_STATUS_* on error
 */
sword_t or(struct erric_t *erric, sword_t i, sword_t j, enum format_t format);

/**
 * @brief Rj BITWISE AND Ri
 * Applies the AND operator to every bit of Rj and Ri and stores the result in Rj
 *
 * @param[in] erric - pointer to erric structure
 * @param[in] i	- no. of register
 * @param[in] j	- no. of register
 * @param[in] format - operation format
 *
 * @returns ERRIC_STATUS_NONE on success, appropriate ERRIC_STATUS_* on error
 */
sword_t and(struct erric_t *erric, sword_t i, sword_t j, enum format_t format);

/**
 * @brief Rj BITWISE XOR Ri
 * Applies the XOR operator to every bit of Rj and Ri and stores the result in Rj
 *
 * @param[in] erric - pointer to erric structure
 * @param[in] i	- no. of register
 * @param[in] j	- no. of register
 * @param[in] format - operation format
 *
 * @returns ERRIC_STATUS_NONE on success, appropriate ERRIC_STATUS_* on error
 */
sword_t xor(struct erric_t *erric, sword_t i, sword_t j, enum format_t format);

/**
 * @brief Rj = Ri << 1
 * Logically shifts the contents of Ri one bit left and puts it into Rj
 * The rightmost bit of the shifted value is lost in Rj
 *
 * @param[in] erric - pointer to erric structure
 * @param[in] i	- no. of register
 * @param[in] j	- no. of register
 * @param[in] format - operation format
 *
 * @returns ERRIC_STATUS_NONE on success, appropriate ERRIC_STATUS_* on error
 */
sword_t lsl(struct erric_t *erric, sword_t i, sword_t j, enum format_t format);

/**
 * @brief *Rj >> *Ri
 * Logically shifts the contents of Ri one bit right and puts it into Rj
 * The leftmost bit of the shifted value is lost in Rj
 *
 * @param[in] erric - pointer to erric structure
 * @param[in] i	- no. of register
 * @param[in] j	- no. of register
 * @param[in] format - operation format
 *
 * @returns ERRIC_STATUS_NONE on success, appropriate ERRIC_STATUS_* on error
 */
sword_t lsr(struct erric_t *erric, sword_t i, sword_t j, enum format_t format);

#endif //ERRIC_LOGIC_OPERATORS_H
