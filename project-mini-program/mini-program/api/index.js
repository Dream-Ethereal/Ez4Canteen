
import member from './member'

const json = {
	member,
}

export default (name) => new Promise(resolve => resolve(json[name]), 500)