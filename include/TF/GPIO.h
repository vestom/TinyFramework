/*
 * Timer.h
 *
 *  Created on: Oct 19, 2016
 *      Author: tov
 */

#ifndef TF_GPIO_H_
#define TF_GPIO_H_

namespace TF {

class GPIO {
public:
	GPIO() = 0;
	virtual ~GPIO();

	/// Set pin on or off
	void set(bool on);

	/// Set value of pin
	bool get(void);

	enum Port {
	    A = 0,
	    B = 1,
	    C = 2,
	    D = 3,
	    E = 4
	};

};

} /* namespace TF */

#endif /* TF_GPIO_H_ */
