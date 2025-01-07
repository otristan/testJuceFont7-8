#include "MainComponent.h"

#if USE_JUCE7
#include "vf_FreeTypeFaces.h"
#endif

//==============================================================================
MainComponent::MainComponent()
{
  setSize (600, 400);
  
  addAndMakeVisible(&mLabel);
  addAndMakeVisible(&mLabel2);
  
#if USE_JUCE7
  {
    juce::File file = juce::File(__FILE__).getSiblingFile("MyriadPro-Bold.jucefont");
    auto iStream = file.createInputStream();
    juce::Typeface::Ptr typeface = nullptr;
    if (iStream)
    {
      typeface = new juce::CustomTypeface(*iStream);
      auto font = juce::Font(typeface).withPointHeight(18.f);;
      mLabel.setFont(font);
    }
  }
  {
    juce::File file = juce::File(__FILE__).getSiblingFile("DIN.ttf");
    auto iStream = file.createInputStream();
    if (iStream)
    {
      auto block = std::make_shared<juce::MemoryBlock>();
      size_t fileSize = iStream->readIntoMemoryBlock(*block);
      FreeTypeFaces::addFaceFromMemory(file.getFullPathName(), 3.f, 5.f, true, block);
      juce::Typeface::Ptr typeface = FreeTypeFaces::createTypefaceForFont(file.getFullPathName(), 34);
      auto font = juce::Font(typeface).withPointHeight(34.f);
      mLabel2.setFont(font);
    }
  }
#else
  {
    juce::File file = juce::File(__FILE__).getSiblingFile("MyriadPro-Bold.ttf");
    auto iStream = file.createInputStream();
    juce::MemoryBlock block;
    size_t fileSize = iStream->readIntoMemoryBlock(block);
    juce::Typeface::Ptr typeface = juce::Typeface::createSystemTypefaceFor(block.getData(), fileSize);
    
    auto font = juce::Font(juce::FontOptions(typeface)).withPointHeight(18.f);
    mLabel.setFont(font);
  }
  {
    juce::File file = juce::File(__FILE__).getSiblingFile("DIN.ttf");
    auto iStream = file.createInputStream();
    juce::MemoryBlock block;
    size_t fileSize = iStream->readIntoMemoryBlock(block);
    juce::Typeface::Ptr typeface = juce::Typeface::createSystemTypefaceFor(block.getData(), fileSize);
    
    auto font = juce::Font(juce::FontOptions(typeface)).withPointHeight(34.f);
    mLabel2.setFont(font);
  }
#endif
  
  mLabel.setText("Trigger Mode", juce::dontSendNotification);
  mLabel.setJustificationType(juce::Justification::centred);
  mLabel.setColour(juce::Label::textColourId, juce::Colours::white);
  mLabel.setColour(juce::Label::backgroundColourId, juce::Colours::red);
  
  mLabel2.setText("20000Hz", juce::dontSendNotification);
  mLabel2.setJustificationType(juce::Justification::centred);
  mLabel2.setColour(juce::Label::textColourId, juce::Colours::white);
  mLabel2.setColour(juce::Label::backgroundColourId, juce::Colours::red);
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
  g.fillAll(juce::Colours::black);
}

void MainComponent::resized()
{
  mLabel.setSize(200, 50);
  mLabel.setBoundsToFit(juce::Rectangle<int>(0, 0, getWidth(), getHeight()/2), juce::Justification::centred, true);
  mLabel2.setSize(200, 50);
  mLabel2.setBoundsToFit(juce::Rectangle<int>(0, getHeight()/2, getWidth(), getHeight()/2), juce::Justification::centred, true);
}
