<?hh //partial

namespace package\spec;

use package\ClassObject;
use package\ClassNameMatcher;

describe(ClassNameMatcher::class, function () {
  beforeEach(function () {
    $this->classFile = new ClassObject(
      realpath(__DIR__ . '/fixtures/Example1.hh'),
      'package\\spec\\fixtures',
      realpath(__DIR__ . '/fixtures')
    );
  });
  describe('startsWith()', function () {
    beforeEach(function () {
      $this->matcher = ClassNameMatcher::startsWith('Exa');
    });
    context('when matched', function () {
      it('returns true', function () {
        expect($this->matcher->matches($this->classFile))->toBeTrue();
      });
    });
  });
  describe('endsWith()', function () {
    beforeEach(function () {
      $this->matcher = ClassNameMatcher::endsWith('1');
    });
    context('when matched', function () {
      it('returns true', function () {
        expect($this->matcher->matches($this->classFile))->toBeTrue();
      });
    });
  });
});
