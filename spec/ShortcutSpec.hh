<?hh //partial

namespace hhpack\package\spec;

use hhpack\package as package;
use hhpack\package\ClassObject;
use hhpack\package\SourceFile;
use hhpack\package\spec\mock\ResourceMock;
use hhpack\package\spec\fixtures\Base;

describe('package', function () {
  describe('package\startsWith', function () {
    beforeEach(function () {
      $this->item = new ResourceMock('foobar');
    });
    context('when matched', function () {
      it('returns true', function () {
        $matcher = package\startsWith('foo');
        expect($matcher($this->item))->toBeTrue();
      });
    });
  });
  describe('package\endsWith', function () {
    beforeEach(function () {
      $this->item = new ResourceMock('foobar');
    });
    context('when matched', function (){
      it('returns true', function () {
        $matcher = package\endsWith('bar');
        expect($matcher($this->item))->toBeTrue();
      });
    });
  });
  describe('package\implementsInterface', function () {
    beforeEach(function () {
        $this->item = new ClassObject(
            'hhpack\\package\\spec\\fixtures',
            realpath(__DIR__ . '/fixtures'),
            new SourceFile(realpath(__DIR__ . '/fixtures/Example1.hh'))
        );
    });
    context('when unmatched', function (){
      it('returns false', function () {
        $matcher = package\implementsInterface(Iterator::class);
        expect($matcher($this->item))->toBeFalse();
      });
    });
  });
  describe('package\subclassOf', function () {
    beforeEach(function () {
        $this->item = new ClassObject(
            'hhpack\\package\\spec\\fixtures',
            realpath(__DIR__ . '/fixtures'),
            new SourceFile(realpath(__DIR__ . '/fixtures/Example1.hh'))
        );
    });
    context('when matched', function (){
      it('returns ture', function () {
        $matcher = package\subclassOf(Base::class);
        expect($matcher($this->item))->toBeTrue();
      });
    });
    context('when unmatched', function (){
      it('returns false', function () {
        $matcher = package\subclassOf(Iterator::class);
        expect($matcher($this->item))->toBeFalse();
      });
    });
  });
});
