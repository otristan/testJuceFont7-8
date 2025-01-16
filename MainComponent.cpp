#include "MainComponent.h"

#if USE_JUCE7
#include "vf_FreeTypeFaces.h"
#else

class MyLookAndFeel : public juce::LookAndFeel_V4
{
  public:
    juce::TypefaceMetricsKind getDefaultMetricsKind() const override
    {
      return juce::TypefaceMetricsKind::portable;
    }
};

MyLookAndFeel myLookAndFeel;

#endif


//==============================================================================
MainComponent::MainComponent()
{
  setSize (600, 800);
  
  addAndMakeVisible(&mLabel);
  addAndMakeVisible(&mLabel2);
  addAndMakeVisible(&mLabel3);
  addAndMakeVisible(&mLabel4);
  
#if USE_JUCE7
  {
    juce::File file = juce::File(__FILE__).getSiblingFile("MyriadPro-Bold.jucefont");
    auto iStream = file.createInputStream();
    juce::Typeface::Ptr typeface = nullptr;
    if (iStream)
    {
      typeface = new juce::CustomTypeface(*iStream); // ascent = 0.798224389 FWIW
      auto font = juce::Font(typeface).withHeight(28.f);
      mLabel.setFont(font);
      mLabel2.setFont(font);
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
      juce::Typeface::Ptr typeface = FreeTypeFaces::createTypefaceForFont(file.getFullPathName(), 18.f);
      mLabel3.setFont(juce::Font(typeface).withHeight(18.f));
      
      mLabel4.setFont(juce::Font(typeface).withHeight(30.f));
    }
  }
#else
  
  juce::LookAndFeel::setDefaultLookAndFeel(&myLookAndFeel);
  {
    juce::File file = juce::File(__FILE__).getSiblingFile("MyriadPro-Bold-edited.ttf"); // kern pair removed, ascent and descent (898, 250 --> 898, 227 in typo and hhead) change to match jucefont ratio
    auto iStream = file.createInputStream();
    juce::MemoryBlock block;
    size_t fileSize = iStream->readIntoMemoryBlock(block);
    juce::Typeface::Ptr typeface = juce::Typeface::createSystemTypefaceFor(block.getData(), fileSize);
    
    auto font = juce::Font(juce::FontOptions(typeface)).withHeight(28.f*0.9f);
    mLabel.setFont(font);
  }
  {
    juce::File file = juce::File(__FILE__).getSiblingFile("MyriadPro-Bold-edited2.ttf"); // same as edited2 but with 0.9 scaling applied in type ascent/descent hence 997 252 (same ratio)
    auto iStream = file.createInputStream();
    juce::MemoryBlock block;
    size_t fileSize = iStream->readIntoMemoryBlock(block);
    juce::Typeface::Ptr typeface = juce::Typeface::createSystemTypefaceFor(block.getData(), fileSize);
    
    auto font = juce::Font(juce::FontOptions(typeface)).withHeight(28.f);
    mLabel2.setFont(font);
  }
  {
    juce::File file = juce::File(__FILE__).getSiblingFile("DIN.ttf");
    auto iStream = file.createInputStream();
    juce::MemoryBlock block;
    size_t fileSize = iStream->readIntoMemoryBlock(block);
    juce::Typeface::Ptr typeface = juce::Typeface::createSystemTypefaceFor(block.getData(), fileSize);
    
    auto font = juce::Font(juce::FontOptions(typeface)).withHeight(18.f*0.8f);
    mLabel3.setFont(font);
  }
  {
    juce::File file = juce::File(__FILE__).getSiblingFile("DIN-edited.ttf");
    auto iStream = file.createInputStream();
    juce::MemoryBlock block;
    size_t fileSize = iStream->readIntoMemoryBlock(block);
    juce::Typeface::Ptr typeface = juce::Typeface::createSystemTypefaceFor(block.getData(), fileSize);
    
    auto font = juce::Font(juce::FontOptions(typeface)).withHeight(30.f);
    mLabel4.setFont(font);
  }
#endif
  
  mLabel.setText("Trigger Mode", juce::dontSendNotification);
  mLabel.setJustificationType(juce::Justification::centred);
  mLabel.setColour(juce::Label::textColourId, juce::Colours::white);
  mLabel.setColour(juce::Label::backgroundColourId, juce::Colours::red);
  
  mLabel2.setText("Trigger Mode", juce::dontSendNotification);
  mLabel2.setJustificationType(juce::Justification::centred);
  mLabel2.setColour(juce::Label::textColourId, juce::Colours::white);
  mLabel2.setColour(juce::Label::backgroundColourId, juce::Colours::red);
  
  mLabel3.setText("20000Hz", juce::dontSendNotification);
  mLabel3.setJustificationType(juce::Justification::centred);
  mLabel3.setColour(juce::Label::textColourId, juce::Colours::white);
  mLabel3.setColour(juce::Label::backgroundColourId, juce::Colours::red);
  
  mLabel4.setText("20000Hz", juce::dontSendNotification);
  mLabel4.setJustificationType(juce::Justification::centred);
  mLabel4.setColour(juce::Label::textColourId, juce::Colours::white);
  mLabel4.setColour(juce::Label::backgroundColourId, juce::Colours::red);
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
  g.fillAll(juce::Colours::black);
}

void MainComponent::resized()
{
  std::array<juce::Component*, 4> widgets = {&mLabel, &mLabel2, &mLabel3, &mLabel4};
  
  for (int i = 0; i < widgets.size(); i++)
  {
    widgets[i]->setSize(200, 50);
    widgets[i]->setBoundsToFit(juce::Rectangle<int>(0, i*getHeight()/(float)widgets.size(), getWidth(), getHeight()/(float)widgets.size()), juce::Justification::centred, true);
  }
}
