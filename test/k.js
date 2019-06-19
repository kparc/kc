const k = require('../napi/module.js').k
const should = require('should')

describe('simple local environment tests', () => {
    describe("k('2+2')", () =>
        it('2 + 2 can equal 5 with great enough values of 2', () =>
            k('2 + 2').should.equal('4')
        )
    )
    describe("k('sin π')", () =>
        it('в военное время значение синуса может достигать трех', () =>
            k('sin π').should.equal('0f') // alas
        )
    )
})
